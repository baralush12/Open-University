/*This class represents JavaFX app that represent canvas that contain the temperature average for each month with char-bar, and can watch from 2017-2022 average weather*/

import javafx.fxml.FXML;
import javafx.scene.canvas.Canvas;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.paint.Color;

public class GraphicController {
	final double[][] temperatures = {
            {5, 10, 15, 20, 25, 30, 35, 30, 25, 20, 15, 10},  // 2017
            {7, 12, 17, 22, 27, 32, 37, 32, 27, 22, 17, 12},  // 2018
            {10, 15, 20, 25, 30, 35, 40, 35, 30, 25, 20, 15}, // 2019
            {8, 13, 18, 23, 28, 33, 38, 33, 28, 23, 18, 13},  // 2020
            {6, 11, 16, 21, 26, 31, 36, 31, 26, 21, 16, 11},  // 2021
            {9, 14, 19, 24, 29, 34, 39, 34, 29, 24, 19, 14}   // 2022
    };
	final String[] months = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"};
	final double maxTemp = 40;
	final double minTemp = 0;
	private int currYear = 2017;
	private double tempRange = maxTemp - minTemp;
    @FXML
    private Canvas canv;
    
    private GraphicsContext gc;

    public void initialize() {
        gc = canv.getGraphicsContext2D();  
        createBar();
    }
    private void createBar() {
        //clear canvas
        gc.clearRect(0, 0, canv.getWidth(), canv.getHeight());

        // define the bars size
        double barWidth = canv.getWidth() * 0.4;
        double barHeight = canv.getHeight() * 0.5;
        double xAxis = canv.getWidth() * 0.1;
        double yAxis = canv.getHeight() * 0.9;

        // bar width and gap between bars
        double bWidth = barWidth / temperatures.length;
        double bGap = bWidth * 0.1;

        // find highest and lowest temperature for the current year
        double maxTemp = Double.MIN_VALUE;
        double minTemp = Double.MAX_VALUE;
        for (double temp : temperatures[currYear - 2017]) {
            maxTemp = Math.max(maxTemp, temp);
            minTemp = Math.min(minTemp, temp);
        }
        
        // draw the bars
        for (int i = 0; i < temperatures[currYear - 2017].length; i++) {
            double temp = temperatures[currYear - 2017][i];
            double bHeight = temp / maxTemp * barHeight;
            double barX = xAxis + i * (bWidth + bGap) + bGap / 2;
            double barY = yAxis - bHeight;

            // set the fill color based on the temperature value
            if (temp == maxTemp) {
                gc.setFill(Color.RED);
            } else if (temp == minTemp) {
                gc.setFill(Color.BLUE);
            } else {
                gc.setFill(Color.GRAY);
            }

            gc.fillRect(barX, barY, bWidth - bGap, bHeight);
            gc.setFill(Color.BLACK);
            gc.fillText(months[i], barX + bWidth / 2 - 10, yAxis + 20);
        }
        // Draw y-axis labels
        for (int i = 0; i <= 5; i++) {
            double temp = minTemp + (tempRange / 5 * i);
            double labelY = yAxis - i * barHeight / 5;
            gc.setFill(Color.BLACK);
            gc.fillText(String.format("%.0f", temp), xAxis - 30, labelY + 5);
        }

        //gc.fillText("Year: " + currYear, xAxis + barWidth / 2 - 20, yAxis - barHeight - 20);
        gc.fillText("Year: " + currYear, barWidth + 100, barHeight - 250);
    }
    @FXML
    public void nextYear() {
    	if(currYear == 2022) {
    		currYear = 2017;
    	}else {
    		currYear++;
    	}
       createBar();
    }
}