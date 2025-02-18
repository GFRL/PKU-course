import numpy as np
from HM1_Convolve import Gaussian_filter, Sobel_filter_x, Sobel_filter_y
from utils import read_img, write_img

def compute_gradient_magnitude_direction(x_grad, y_grad):
    """
        The function you need to implement for Q2 a).
        Inputs:
            x_grad: array(float) 
            y_grad: array(float)
        Outputs:
            magnitude_grad: array(float)
            direction_grad: array(float) you may keep the angle of the gradient at each pixel
    """
    magnitude_grad = np.sqrt(x_grad**2 + y_grad**2)
    direction_grad = np.arctan2(y_grad, x_grad)
    return magnitude_grad, direction_grad 



def non_maximal_suppressor(grad_mag, grad_dir):
    """
        The function you need to implement for Q2 b).
        Inputs:
            grad_mag: array(float) 
            grad_dir: array(float)
        Outputs:
            output: array(float)
    """
    ZS = ((grad_dir >= np.pi / 8 * 1) & (grad_dir < np.pi / 8 * 3) | (grad_dir >= -np.pi / 8 * 7) & (grad_dir < -np.pi / 8 * 5))
    S  = ((grad_dir >= np.pi / 8 * 3) & (grad_dir < np.pi / 8 * 5) | (grad_dir >= -np.pi / 8 * 5) & (grad_dir < -np.pi / 8 * 3))
    YS = ((grad_dir >= np.pi / 8 * 5) & (grad_dir < np.pi / 8 * 7) | (grad_dir >= -np.pi / 8 * 3) & (grad_dir < -np.pi / 8 * 1))
    O  = ((grad_dir >= np.pi / 8 * 7) | (grad_dir <-np.pi / 8 * 7) | (grad_dir >= -np.pi / 8 * 1) & (grad_dir <  np.pi / 8 * 1))
    
    n, m = grad_mag.shape
    
    T = np.zeros(grad_mag.shape)
    T[1:,1:] = grad_mag[:n-1,:m-1]
    ZS = ZS & (grad_mag >= T)

    T = np.zeros(grad_mag.shape)
    T[:n-1,:m-1] = grad_mag[1:,1:]
    ZS = ZS & (grad_mag >= T)

    T = np.zeros(grad_mag.shape)
    T[1:,:] = grad_mag[:n-1,:]
    S = S & (grad_mag >= T)

    T = np.zeros(grad_mag.shape)
    T[:n-1,:] = grad_mag[1:,:]
    S = S & (grad_mag >= T)

    T = np.zeros(grad_mag.shape)
    T[1:,:m-1] = grad_mag[:n-1,1:]
    YS = YS & (grad_mag >= T)

    T = np.zeros(grad_mag.shape)
    T[:n-1,1:] = grad_mag[1:,:m-1]
    YS = YS & (grad_mag >= T)

    T = np.zeros(grad_mag.shape)
    T[:,1:] = grad_mag[:,:m-1]
    O = O & (grad_mag >= T)

    T = np.zeros(grad_mag.shape)
    T[:,:m-1] = grad_mag[:,1:]
    O = O & (grad_mag >= T)

    NMS_output = grad_mag * (ZS | S | YS | O)
    return NMS_output

           


def hysteresis_thresholding(img) :
    """
        The function you need to implement for Q2 c).
        Inputs:
            img: array(float) 
        Outputs:
            output: array(float)
    """


    #you can adjust the parameters to fit your own implementation 
    low_ratio = 0.10
    high_ratio = 0.30
    
    row, col = img.shape
    output=np.zeros((row,col))
    
    for i in range(row):
        for j in range(col):
            if img[i,j]>high_ratio:
                output[i,j]=1
    #开始蔓延
    while True:
        flag=False
        for i in range(row):
            for j in range(col):
                if output[i,j]==1:
                    for x in range(-1,2):
                        for y in range(-1,2):
                            if i+x>=0 and i+x<row and j+y>=0 and j+y<col:
                                if img[i+x,j+y]>low_ratio and output[i+x,j+y]==0:
                                    output[i+x,j+y]=1
                                    flag=True
        if not flag:
            break

    return output 



if __name__=="__main__":

    #Load the input images
    input_img = read_img("lenna.png")/255

    #Apply gaussian blurring
    blur_img = Gaussian_filter(input_img)

    x_grad = Sobel_filter_x(blur_img)
    y_grad = Sobel_filter_y(blur_img)

    #Compute the magnitude and the direction of gradient
    magnitude_grad, direction_grad = compute_gradient_magnitude_direction(x_grad, y_grad)

    #NMS
    NMS_output = non_maximal_suppressor(magnitude_grad, direction_grad)

    #Edge linking with hysteresis
    output_img = hysteresis_thresholding(NMS_output)
    
    write_img("result/HM1_Canny_result.png", output_img*255)
