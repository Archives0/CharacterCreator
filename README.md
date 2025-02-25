# Moddable Character Creator
 This character creation system is made for classic roleplaying games where the player's main visual representation is through static portraits.

 ## How it Works

 When the CharCreator is instantiated, it will check the player's launch directory and create any default files which may be missing. If launched in the editor, this directory will be in **C:\Program Files (x86)\Epic Games\Launcher\Portal\Binaries\Win64**. When launching a built application, this directory will be in a more reasonable location.
 If any default files are misssing, they will be repopulated with hardcoded values.

### Adding a New Race

To add a new race, create a .txt file inside the **Data / Races** directory which contains the text description you would like the race to have in the character creation screen.

In the **Data / Races / Portraits** directory, create a folder with the same name as your newly created race. Here, you can add any photos you would like to have as options for your custom race.

### Adding a New Class

To add a new class, create a .txt file inside the **Data / Classes** directory with the name of your desired class. Like the race file, the contents of your class file should define the description you would like the class to have in the character creation screen.

### Custom Stat Bonuses

Both the player's race and class provide a stat bonus for the player. To define a custom bonus, create a .txt file in **Data / Races / Stats** and/or **Data / Classes / Stats** named identically to your custom race and/or class.

The contents fo the file will be parsed and decoded in order to determine what bonuses or detriments the race or class should have. As of the time fo writing, the program will only decode the stat file in the following format:

strength | constitution | dexterity | intelligence | willpower | charisma

The program will recognize the following characters with the corresponding stat effects:

**+:** +2 to stat<br>
**0:** No effect<br>
**-:** -2 to stat<br>

If no stat file has been defined for a custom race or class, a default statblock will be assigned which has no bonuses or detriments.
