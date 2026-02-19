WARNING: sorry for bd english and this is still a prototype ad work in progress.
XNSS new programming language!!!! note: to work it requires Visual C++ Redistributable
its open source and similar to python. so it should be pretty easy to learn cuz its all logic.
FUNDEMANTAL COMMANDS:
end.work = project finished
import = adds a variables like on python
write("") = writes text and the text shall be put inside the "" so its will be like this (ex. write("Hello World!"))
create.list[] = creates a list and can also be named with list.name(""). the objects in the list must be separated with a ","
create.object("") = creates an object that can be used as a command in the ide. (ex. create.object("cube") cube = 2 write("cube") and the output will be 2)
COMMANDS TO RUN THE FILE
./xnss_engine.exe = runs a .xnss file
VARIABLES
random = its a random choice maker mostly used in lists (for example create.list[1,2,3,4,5] // lets give the list a name. list.name("list 1") // now lets put it in the random. random.choice(list 1) and the output will be a choice of whatever is in the list but will be random)
draw = like turtle in python but has configured commands to draw shapes and lines.
DRAW COMMANDS
draw.line(x: y:) = it draws a line and the x and y are to configure how much long it needs to be NOTE: apparently on draw.line(x: y:) can only be chosen one. you cant use both x and y at the same time!
draw.line.curve(x: y:) = it draws a line and it makes it curve and it works where you can now use both x and y and it works that by the distance of x the y will go up until the x arrives to the end of its desired distance.
draw.square(L:) = it draws a square and the l stands for the line segments in fact since the square's line segments are equal you are only requested to input whatever distance you want
draw.circle(R:) = it draws a circle and the r stands for radius so that you are only requested to input the distance of the radius
draw.pos(x: y:) = it is a very important command in draw because it determines the position of where to put your shape line whatever. NOTE: this is obligatory after inputting the command of whatever you are drawing (for ex. draw.line(x:7 y:0) draw.pos(x:12 y:12)
) and also that the position x:0 y:0 will be the bottom of the screen.
draw.color(R: G: B:) = its used to input colors and to be more precise it uses the rgb formats.
RANDOM COMMANDS
random.choice() = input the name of whatever list you are like making it do a random choice.


                                                                           BY Lorenzo.