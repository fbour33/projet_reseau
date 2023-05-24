package client;

public class Goal {
    public int x;
    public int y;
    public int time;
    public int timeLeft;

    public Goal(int x, int y, int time){
        this.x=x;
        this.y=y;
        this.time = time;
        timeLeft = time;
    }

}