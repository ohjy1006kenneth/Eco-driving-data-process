**Overview**

I worked on the Eco driving project this semester. Eco driving is a
driving behavior that is created for a goal to reduce energy
consumption. Eco driving is useful because it is beneficial for the
environment (fuel saving, less emissions) and can even save some money
with less fuel consumption. The problem with normal human driving
behavior is that when humans drive vehicles in traffic light situations,
they make unnecessary stops and goes which lower energy efficiency. What
if we use automated driving and other technologies to prevent those
unnecessary stops and increase energy efficiency? This was the question
that we wanted to get out of the project.

**Experiment Procedure**

For the experiment, we had two traffic lights that were put apart from
each other and made the vehicle pass them. We had two different traffic
light timing plans: Synthetic and Peachtree. Synthetic plan had 3
scenarios in it. The scenarios differed from one another either by
timing offset of two traffic lights, or different vehicle entry time.
Peachtree plan was chosen from a real-life traffic light data and also
had 3 scenarios. Unfortunately, we could only test 2 scenarios for
Peachtree because of the weather. We drove through the traffic light
situation with three different driving methods (HV, ACC, CAV) and
collected log data. HV stands for human driven vehicle, and it was the
default driving method where the human stops when red light and
accelerate when green light. ACC is a human driven vehicle but with the
assistance of adaptive cruise control. CAV stands for Connected and
Automated Vehicles and was the driving method where automated driving
controls the speed of the vehicle to minimize stops between traffic
lights. We ran through all the timing plans and scenarios in them and
collected log data ![A screenshot of a computer Description
automatically generated](./media/image1.png)

which collected three things: Mass Air Flow, SOC
(Battery State of Charge), and Speed.

The log file looked like the picture shown above and needed
to be post processed to do data acquisition.**\
**

**Post Processing**

To do data acquisition, firstly I needed to do some filtering and format
exchange. I decided to change this .trc file into csv file so I wrote a
C code that will do exactly that. The code will be in the GitHub
repository that will be linked at the end of this document for detail.
Then, I thought of a way to combine battery energy consumption and
engine fuel consumption. I did this by converting every energy
consumption into Joules. There will be more description of the
methodology in the code inside the GitHub repository.

**Insight**

I compared data for the Peachtree plan and the result were following:

ACC Scenario 1: Total Energy = 220660.3 kJ

![A graph with red lines and black text Description automatically
generated](./media/image2.png)

CAV Scenario 1: Total Energy = 208283.4 kJ

![A graph showing a line Description automatically generated with medium
confidence](./media/image3.png)

HV Scenario 1: Total Energy = 275228.2 kJ

![A graph with red lines Description automatically
generated](./media/image4.png)

ACC Scenario 3: Total Energy = 389015.9 kJ

![A graph with orange lines Description automatically
generated](./media/image5.png)

CAV Scenario 3: Total Energy = 177669.8 kJ

![A graph with a line going up Description automatically
generated](./media/image6.png)

HV Scenario 3: Total Energy = 296110 kJ

![A graph with red lines and white text Description automatically
generated](./media/image7.png)

As the result shows, for Scenario1, CAV were the most energy efficient
followed by ACC and HV. For Scenario 3, CAV were the most energy
efficient followed by HV and ACC.

This can conclude that in the Peachtree traffic plan, CAV is the most
energy efficient while CAV and HV are less energy efficient. This result
can tell us that CAV can be utilized in eco driving.
