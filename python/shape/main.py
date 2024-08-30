import cv2 as cv
import numpy as np
import pandas as pd

left_csv = "inside/left.csv"
right_csv = "inside/right.csv"
lane_csv = "inside/lane.csv"
mask_csv = "inside/mask.csv"

image_height = 600
image_width = 800

def readCSV(lane_csv, mask_csv):
    lane = pd.read_csv(lane_csv, header=None)
    mask = pd.read_csv(mask_csv, header=None)
    
    image = np.zeros((image_height, image_width), dtype=np.uint8)
    
    lane = np.array(lane)
    mask = np.array(mask)
    
    lane[lane > 0.2] = 255
    mask[mask > 0.2] = 255
    
    image[lane == 255] = 255
    image[mask == 255] = 255
    
    cv.imwrite("output.png", image)

if __name__ == "__main__":
    readCSV(lane_csv, mask_csv)