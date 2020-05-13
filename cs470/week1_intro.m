 %% Vector indexing in Matlab
grades = [99,90,79,85,88];
grades(2) = 8

%% Vector indexing in Matlab - different ways
grades = [99,90,79,85,88];

grades(1:5)
grades(1:2:5)
grades([1,5])
grades(1:end)

%% Matrices in Matlab
% Matrix 1. No semi-colon at the end of statement, so output is not suppressed on command window
A=[1 2 3; 4 5 6]

% Matrix 2. Semi-colon at the end of statement, so output is suppressed on
% command window (but note value of A is updated)
A=[7 3 6; 5 1 4;2 9 8];

%% Reading gray level image
imgray = imread('moon.tif');
figure, imshow(imgray), impixelinfo %Pixel information is shown in (x, y) coordinate system

%% Reading RGB image
imrgb = imread('football.jpg');
figure, imshow(imrgb), impixelinfo

%% Converting RGB to Gray image
imconvert2gray = rgb2gray(imrgb);
figure, imshow(imconvert2gray), impixelinfo

%% Reading and writing Images
clear all;close all;clc;

% - imread. Image reading from disk.
I1 = imread('football.jpg');
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% - imshow, Showing images in matlab.
figure;
imshow(I1);

%Showing the R, G, B channels separately
figure;imshow(I1(:,:,1));
figure;imshow(I1(:,:,2));
figure;imshow(I1(:,:,3));

% - rgb2gray. Convert color image to grayscale.
I2 = rgb2gray(I1);

figure;
imshow(I2);

imwrite(I2,'football_gray.jpg');

[rows cols chan]=size(I2);

whos

%close all;
%% Loading an indexed image. What issues may arise?
%Caution: Before running this section, make sure you have downloaded output_images.zip and added them to Path (using Set Path)

imind = imread('emu.png'); 
figure, imshow(imind), impixelinfo %Verify image looks dull

% This is an indexed image. Show image information
emuinfo = imfinfo('emu.png')

%Get the map of the indexed image
[imind, map] = imread('emu.png');

%And use it show the image. Verify it looks right this time
figure, imshow(imind, map), impixelinfo

%% Convert indexed image to gray and rgb
imind2gray = ind2gray(imind, map);
imind2rgb = ind2rgb(imind, map);

%Now back to indexed
backtoind = rgb2ind(imind2rgb, 64);


%% Loading different kinds of images. Do imfinfo on them to see specific details (see syntax below or write "help imfinfo" on Matlab Command Window)
im = imread('autumn.tif');
figure, imshow(im), impixelinfo

im2 = imread('bag.png');
figure, imshow(im2), impixelinfo

im3 = imread('logo.tif');
figure, imshow(im3), impixelinfo
imfinfo('logo.tif')

im4 = imread('circles.png');
figure, imshow(im4), impixelinfo

im5 = imread('text.png');
figure, imshow(im5), impixelinfo
size(im5)
