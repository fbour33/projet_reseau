package projet_reseau;

import javafx.scene.control.TextArea;

public class Parser {
    private Console console;

    public Parser(Console c, TextArea textarea) {
        console = c;
        console.output = textarea;
    }

    synchronized public void parserAction(String inputParser){
        String[] args = inputParser.split (" ");
        switch(args[0]){
            case "hello":
            if (args.length == 4 || args.length == 1){
                console.output.appendText("hello");
            }else{
                console.output.appendText("< NOK. Usage : 'hello' or 'hello in as ID'" + System.lineSeparator());
            }

            case "log" :
                if (args.length == 2 && args[1].contentEquals("out")) {
                }
                else
                    console.output.appendText("< NOK. Usage : 'log out'" + System.lineSeparator());
                break;
            case "status" :
                if (args.length == 1) {
                }
                else
                    console.output.appendText("< NOK. The command 'status' doesn't expect arguments." + System.lineSeparator());
                break;
            case "addFish":
                if (args.length == 6) {
                   
                }
                else
                    console.output.appendText("< NOK. Usage : addFish 'name' at 'x'x'y', 'w'x'h', 'mobilityModel'" + System.lineSeparator());
                break;
            case "startFish":
                if (args.length == 2) {
                    
                }
                else
                    console.output.appendText("< NOK. Usage : 'startFish name'" + System.lineSeparator());
                break;
            case "delFish":
                if (args.length == 2) {
                   
                }
                else
                    console.output.appendText("< Wrong syntax ! Usage : 'delFish name'" + System.lineSeparator());
                break;
            case "getFishes":
                if (args.length == 1) {
                }
                else
                    console.output.appendText("< NOK. Usage : 'getFishes'" + System.lineSeparator());
                break;
            case "getFishesContinuously":
                if (args.length == 1) {
                }
                else
                    console.output.appendText("< NOK. Usage : 'getFishesContinuously'" + System.lineSeparator());
                break;
            default:
                console.output.appendText("< NOK. Commande introuvable. (Les commandes sont disponible dans l'onglet)." + System.lineSeparator());
                break;
        }
    }
}
