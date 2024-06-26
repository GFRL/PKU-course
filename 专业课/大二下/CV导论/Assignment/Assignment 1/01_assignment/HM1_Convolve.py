import numpy as np
from utils import read_img, write_img

def padding(img, padding_size, type):
    """
        The function you need to implement for Q1 a).
        Inputs:
            img: array(float)
            padding_size: int
            type: str, zeroPadding/replicatePadding
        Outputs:
            padding_img: array(float)
    """
    row, col = img.shape
    if type=="zeroPadding":
        padding_img = np.zeros((row+2*padding_size, col+2*padding_size))
        padding_img[padding_size:padding_size+row, padding_size:padding_size+col] = img #赋值
        return padding_img
    elif type=="replicatePadding":
        padding_img = np.zeros((row+2*padding_size, col+2*padding_size))
        padding_img[padding_size:padding_size+row, padding_size:padding_size+col] = img #赋值

        #上下左右分别复制
        padding_img[:padding_size, padding_size:padding_size+col] = img[0,:]
        padding_img[padding_size+row:, padding_size:padding_size+col] = img[-1,:]
        padding_img[padding_size:padding_size+row, :padding_size] = img[:,0].reshape(-1,1)
        padding_img[padding_size:padding_size+row, padding_size+col:] = img[:,-1].reshape(-1,1)#reshape(-1,1)中-1表示自动计算行数
        #四个角分别复制
        padding_img[:padding_size, :padding_size] = img[0,0]
        padding_img[:padding_size, padding_size+col:] = img[0,-1]
        padding_img[padding_size+row:, :padding_size] = img[-1,0]
        padding_img[padding_size+row:, padding_size+col:] = img[-1,-1]
        return padding_img


def convol_with_Toeplitz_matrix(img, kernel):
    """
        The function you need to implement for Q1 b).
        Inputs:
            img: array(float) 6*6
            kernel: array(float) 3*3
        Outputs:
            output: array(float)
    """
    #zero padding
    padding_size = 1
    padding_img = padding(img, 1, "zeroPadding").reshape(-1,1)#转化成一维数组,size=(row+2)*(col+2)
    row, col = img.shape#可支持不同大小的img
    #build the Toeplitz matrix and compute convolution
    #思路：kernel转化成Toeplitz矩阵的一行，然后复制多次，最后reshape成Toeplitz矩阵 size ( row*col,(row+2)*(col+2))
    tmp_row=kernel[0]+[0]*(col-1)+kernel[1]+[0]*(col-1)+kernel[2]+[0]*(col-1)+[0]*( (row-1)*(col+2) + 1)
    #这个比标准的一行多了一个0，这样子就好处理，size=1,(row+2)*(col+2)+1,一共要重复row*cow行
    tmp1_row=tmp_row*col+[0]*2
    #重复6次后换行，要多加两个0
    tmp2_row=tmp1_row*row
    #最后reshape就好了
    Toeplitz_matrix = tmp2_row[:row*col*(row+2)*(col+2)].reshape(row*col,(row+2)*(col+2))
    output = np.dot(Toeplitz_matrix, padding_img).reshape(row, col)


    return output


def convolve(img, kernel):
    """
        The function you need to implement for Q1 c).
        Inputs:
            img: array(float)
            kernel: array(float)
        Outputs:
            output: array(float)
    """
    row, col = img.shape
    kernel_length=kernel.shape[0]
    #build the sliding-window convolution here
    i0=np.repeat(np.arange(row-kernel_length+1),kernel_length)
    j0=np.tile(np.arange(col-kernel_length+1),kernel_length)
    i,j=np.meshgrid(i0,j0,indexing='ij')
    windows=img[i[...,np.newaxis]+np.arange(kernel_length),
                j[...,np.newaxis]+np.arange(kernel_length)]
    kernel=kernel.flatten()
    output=np.dot(windows.reshape(-1, kernel_length**2), kernel)
    output=output.reshape(row-kernel_length+1, col-kernel_length+1)
    return output


def Gaussian_filter(img):
    padding_img = padding(img, 1, "replicatePadding")
    gaussian_kernel = np.array([[1/16,1/8,1/16],[1/8,1/4,1/8],[1/16,1/8,1/16]])
    output = convolve(padding_img, gaussian_kernel)
    return output

def Sobel_filter_x(img):
    padding_img = padding(img, 1, "replicatePadding")
    sobel_kernel_x = np.array([[-1,0,1],[-2,0,2],[-1,0,1]])
    output = convolve(padding_img, sobel_kernel_x)
    return output

def Sobel_filter_y(img):
    padding_img = padding(img, 1, "replicatePadding")
    sobel_kernel_y = np.array([[-1,-2,-1],[0,0,0],[1,2,1]])
    output = convolve(padding_img, sobel_kernel_y)
    return output



if __name__=="__main__":

    np.random.seed(111)
    input_array=np.random.rand(6,6)
    input_kernel=np.random.rand(3,3)


    # task1: padding
    zero_pad =  padding(input_array,1,"zeroPadding")
    np.savetxt("result/HM1_Convolve_zero_pad.txt",zero_pad)

    replicate_pad = padding(input_array,1,"replicatePadding")
    np.savetxt("result/HM1_Convolve_replicate_pad.txt",replicate_pad)


    #task 2: convolution with Toeplitz matrix
    result_1 = convol_with_Toeplitz_matrix(input_array, input_kernel)
    np.savetxt("result/HM1_Convolve_result_1.txt", result_1)

    #task 3: convolution with sliding-window
    result_2 = convolve(input_array, input_kernel)
    np.savetxt("result/HM1_Convolve_result_2.txt", result_2)

    #task 4/5: Gaussian filter and Sobel filter
    input_img = read_img("lenna.png")/255

    img_gadient_x = Sobel_filter_x(input_img)
    img_gadient_y = Sobel_filter_y(input_img)
    img_blur = Gaussian_filter(input_img)

    write_img("result/HM1_Convolve_img_gadient_x.png", img_gadient_x*255)
    write_img("result/HM1_Convolve_img_gadient_y.png", img_gadient_y*255)
    write_img("result/HM1_Convolve_img_blur.png", img_blur*255)




    