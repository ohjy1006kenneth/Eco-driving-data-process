#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char** argv){
	int message_num, type, id, data_length;
	float time_offset;
	float prev_soc = 0.0;
	float prev_soc_time = 0.0;
	float prev_maf = 0.0;
	float prev_maf_time = 0.0;
	float efc = 0.0;
	float bec = 0.0;
	unsigned int data[10];
	char buf[2048];
	int print_joules = 0;

	// Read .trc file
	FILE *f = fopen(argv[1], "r");

	//Ignore first 14 line
	for(int i = 0; i < 14; ++i){
		fgets(buf, 2048, f);
	}

	// Ignore until car starts moving
	while(1) {
		fscanf(f, "%d)", &message_num);
		fscanf(f, "%f", &time_offset);
		fscanf(f, "%s", buf);

		if(buf[0]=='R')type=0;
			else type=1;
		

		fscanf(f,"%x", &id);
		fscanf(f,"%x", &data_length);
		for(int i = 0; i < data_length; i++){
			fscanf(f,"%x", &data[i]);
		}

		if (id == 0x07E8 && data[2] == 0x0D && data[3] != 0) {
			printf("%s,%s,%s,%s,%s,%s,%s\n", "Message Number", "Time Offset (ms)", "Type", "ID (hex)", "Data Length", "Data Bytes", "Total Energy Consumption (kJ)");
			break;
		}
	}
	
	while(!feof(f)){
		fscanf(f, "%d)", &message_num);
		fscanf(f, "%f", &time_offset);
		fscanf(f, "%s", buf);

		if(buf[0]=='R')type=0;
			else type=1;
		

		fscanf(f,"%x", &id);
		fscanf(f,"%x", &data_length);
		for(int i = 0; i < data_length; i++){
			fscanf(f,"%x", &data[i]);
		}

		if (id == 0x07E8) {
			// It is speed signal
			if (data[2] == 0x0D) {
				printf("%d,%f,%d,%s,%d,", message_num, time_offset, type, "07E8-0D", data_length);
				printf("%d km/h\n", data[3]);
			}
			
			// It is Mass air flow signal
			if (data[2] == 0x10) {
				// hex2dec(fourth) = A, hex2dec(fifth) = B, the MAF = (256*A+B)/100)
				int maf = (256 * data[3]) / 100;
				
				if (prev_maf == 0.0) {
					prev_maf = maf;
				}

				if (maf != 0) { // Ignore 0 values
					if(prev_maf != maf) {
						float time_passed = (time_offset - prev_soc_time) * 0.001; // In seconds
						// 14.6 = stoichiometric air-fuel ratio
						efc = ((maf / 14.6) * 44.4) * time_passed; //engine fuel consumption in kJ. (44.4kJ per gram of gasoline)
						print_joules = 1;
					}

					printf("%d,%f,%d,%s,%d,", message_num, time_offset, type, "07E8-10", data_length);
					printf("%d g/s\n", maf);

					prev_maf = maf;
				}
			}
		}

		// It is battery state of charge
		if (id == 0x07EC) {
			// SOC = (256*A+B)/1000 where fifth byte(A) and sixth byte(B)
			float soc = (256.0*data[4] + data[5]) / 1000.0;

			// Set prev_soc if was not set
			if (prev_soc == 0.0) {
				prev_soc = soc;
			}

			if (soc != 0.0) { // Ignore 0 values
				if (print_joules == 1) {
					float soc_diff = soc - prev_soc;
					//mAh * voltage * 3.6 = Joules of energy -> convert to kJ
					bec = (6500 * soc_diff) * 288 * 3.6 * 0.001;  // got values for mAh and voltage of car battery at https://ennocar.com/product/lincoln-mkz-hybrid-battery-2010-2012/#:~:text=Voltage%3A%20288V,Battery%20Capacity%3A%206500%20mAh
					prev_soc = soc;
					print_joules = 0;
					// Output total energy consumption after whenever mass air flow value has changed
					printf("%d,%f,%d,%s,%d,", message_num, time_offset, type, "07EC", data_length);
					printf("%.2f %%, %.2fkJ\n", soc, efc + bec);
				}

				printf("%d,%f,%d,%s,%d,", message_num, time_offset, type, "07EC", data_length);
				printf("%.2f %%\n", soc);
			}
		}
	}
}
