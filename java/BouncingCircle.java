import javafx.animation.AnimationTimer;
import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.canvas.Canvas;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.layout.StackPane;
import javafx.scene.media.AudioClip;
import javafx.stage.Stage;

public class BouncingCircle extends Application
{
    
    private static final int WIDTH = 400;
    private static final int HEIGHT = 400;
    private static final int OUTER_CIRCLE_RADIUS = 180;
    private static final int INNER_CIRCLE_RADIUS = 20;
    private double centerX = WIDTH / 2.0;
    private double centerY = HEIGHT / 2.0;
    private double circleX = centerX;
    private double circleY = centerY - OUTER_CIRCLE_RADIUS + INNER_CIRCLE_RADIUS;
    private double speedX = 2.0;
    private double speedY = 2.0;
    private GraphicsContext gc;
    private AudioClip dingSound;

    public static void main(String[] args)
    {
        launch(args);
    }

    @Override
    public void start(Stage primaryStage)
    {
        primaryStage.setTitle("Bouncing Circle");
        Canvas canvas = new Canvas(WIDTH, HEIGHT);
        gc = canvas.getGraphicsContext2D();
        dingSound = new AudioClip(getClass().getResource("ding.mp3").toString());
        StackPane root = new StackPane();
        root.getChildren().add(canvas);
        primaryStage.setScene(new Scene(root));
        primaryStage.show();

        new AnimationTimer()
        {
            @Override
            public void handle(long now)
            {
                update();
                draw();
            }
        }.start();
    }

    private void update()
    {
        circleX += speedX;
        circleY += speedY;

        // Check for collision with the outer circle
        double distance = Math.sqrt(Math.pow(circleX - centerX, 2) + Math.pow(circleY - centerY, 2));
        if (distance >= OUTER_CIRCLE_RADIUS - INNER_CIRCLE_RADIUS)
        {
            // Reverse direction
            speedX *= -1;
            speedY *= -1;
            // Play ding sound
            dingSound.play();
        }
    }

    private void draw()
    {
        // Clear the canvas
        gc.clearRect(0, 0, WIDTH, HEIGHT);

        // Draw outer circle
        gc.strokeOval(centerX - OUTER_CIRCLE_RADIUS, centerY - OUTER_CIRCLE_RADIUS, OUTER_CIRCLE_RADIUS * 2, OUTER_CIRCLE_RADIUS * 2);

        // Draw inner circle
        gc.fillOval(circleX - INNER_CIRCLE_RADIUS, circleY - INNER_CIRCLE_RADIUS, INNER_CIRCLE_RADIUS * 2, INNER_CIRCLE_RADIUS * 2);
    }
}
