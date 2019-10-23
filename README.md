# Arup Stem Workshop

Hello and welcome to this workshop hosted by Arup.

## Part 1:
### Introduction to the IoT

IoT stands for Internet of Things. A concept where everything is connected to the internet, from smart devices to your everyday appliances.

So why would you want to connect everything to the internet?

Imagine the amount of Energy consumed when you leave a room and forget to turn off the lights. Or imagine you travel to somewhere really nice and far away, but suddenly you remember you didn't turn off your heater or even worse you forgot to lock your front door!

If there was only a way that you could communicate with these devices from where ever you are and be able to get a notification as to the current state of your front door, or the room temperature in your house right now. You could add a connected sensor that could send a message to the internet letting you know via your favourite app that your if your front door is open and the current temperature of your bedroom.

But it gets even better, you could send a command to turn the heating off and lock the front door!

Now lets take this up a notch, smart fridges, smart stationary, imagine never having to worry about having enough milk in the fridge because your fridge will buy it for you.

### The challenge

 STEM buildings limited has approached Arup with a new and interesting project idea! They want to develop a system that can control meeting room lights from any location.

Arup as a sustainable company is very big on energy savings and creating sustainable environments. As an innovative firm, Arup has opted to use the IoT to solve this problem and has chosen your team to get the job done.

### Fundamental requirements
## Part 2:
### Design and plan
The first step in going to be figuring out how our solution is going to work,
### Purchasing parts
What you need:
 - Breadboard
 - Jumper Cables
 - LEDs
 - Switch
 - Wi-Fi Enabled Microprocessor
 - 1No. 220 Ohms Resistor

 ![alt text](screenshots/220ohmsResistor.PNG "Title Text")

 - 1No. 4.7k Ohms Resistor

 ![alt text](screenshots/47kohmsResistor.PNG "Title Text")

## Part 3:
### Software development
Lets begin by writing some code!

Press the Windows key on your keyboard, type cmd and press the return key.

This window is called the command line or the terminal

![alt text](screenshots/CommandLine.PNG "Title Text")

In the terminal type the following two commands

```
mkdir project
cd project
```

You've just created a folder called "project" using ```mkdir project``` and you've moved into it using ```cd project```

Now we're going to download the Arduino project from our code repository using the command
```cmd
git clone https://gitlab.arup.com/Syed.Hasan/SW.git
cd SW
```

Open the code using the following command

```cmd
start code.ino
```

The editor will look like this

![alt text](screenshots/ArduinoIDE.PNG "Title Text")

The first bit of code we can see are the include statements, which point to libraries our code will need to work.


###Hardware development
##Part 4:
###Testing
###Extra credit

The first group to turn off the LEDs in another group wins the challenge!!
