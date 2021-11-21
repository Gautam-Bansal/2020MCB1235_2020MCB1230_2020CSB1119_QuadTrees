Below described is the debugging process employed to fix an error in the find function, fixed in commit# 44cd39743265113505fe6aa60f1f272277e08771


1. First we see that there is a problem in the find() function, and indirectly in the insert() function

![error in find function](https://cdn.discordapp.com/attachments/819858607537389578/911714417522131075/ss_2.png)


2. Then we mark the breakpoints required to analyze the function during the debugging

![breakpoints added](https://cdn.discordapp.com/attachments/819858607537389578/911714417702498334/ss_3.png)


3. We then start the debugging in Visual Studio Code inbuilt gdb debugger

![start debug](https://cdn.discordapp.com/attachments/819858607537389578/911714417899622485/ss_4.png)


4. We can see the local variables at each step

![local variables](https://cdn.discordapp.com/attachments/819858607537389578/911714418134483015/ss_5.png)


5. During the debugging, we reach this step

![step](https://cdn.discordapp.com/attachments/819858607537389578/911714418352590848/ss_6.png)


6. We see in the local variables that the root node has no children, even though we just initialized one. This means the new nodes are not being linked to their ancestors

![error found](https://cdn.discordapp.com/attachments/819858607537389578/911714418541346866/ss_7.png)


7. The correct function after fixing is

![fixed](https://cdn.discordapp.com/attachments/819858607537389578/911714418860118057/ss_8.png)
