# Bot-save-the-Princess

Princess 'P' is trapped inside a Box-World. The program is designed in such a way that a Bot 'B' saves the princess with minimim path cost.

# How-to-play

- Compile the c file.
- Give the dimension of box as the command-line arguments(say you want to enter the dimension 3x3 then enter "./a.out 3 3").
- Then pattern of input is shown in the example below:
./a.out 3 3
/ - P
- - /
/ - B

another example,
./a.out 3 3
- - P
- - -
- - B

- Here '/' means Block and '-' means free path.
- The results will be in the format 

for the first example:
LEFT TOP TOP RIGHT

for the second example:
TOP TOP
