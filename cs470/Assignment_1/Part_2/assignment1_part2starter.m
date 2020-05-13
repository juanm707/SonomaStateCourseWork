function [matEq, map] = assignment1_part2starter(filename)

img = imread(filename);
[m, n] = size(img); %Obtain width and height of image.

hist = imhist(img); %Histogram of this image
histc = cumsum(hist); %Cumulative histogram

L = 256; %Number of gray levels

%Construct histogram of a perfectly equalized image
%Assuming L bins, each bin will contain (m*n)/L pixels
%TODO: Enter code here to initialize each element of idealHist to (m*n)/L. You don't need a for-loop for this one!
idealHist = zeros(L,1) + (m * n)/L;
idealHistc = cumsum(idealHist); %Cumulative histogram

%Initialize the map that will store the transformation to all zeros. 
%In addition, specify the type 'uint8' to ensure that the transform doesn't go out of bounds [0, 255]
%TODO: Enter code here.
map = zeros(1,L,'uint8');
figure, imshow(img)

for i=1:L
    %For each gray-level, find the **index**  that minimizes the difference
    %between histc(i) and the array idealHistc (defined above) 
    %Avoid for loops! This can be done in couple of statements that 1) finds the difference (stored in an array) and then 2) finds the minimum
    %TODO: Enter code here.
    
    d = abs(idealHistc - histc(i));
    [~, ind] = min(d);
        
    %Index ind is between 1 to 256; %Bring it back to range [0, 255]
    %TODO: FIX code below
    map(i) = ind - 1;
end

%Histogram equalized image is simply applying the map to the image. (see part 1)
%TODO: Enter code here (This will be same as Part 1)
matEq = map(double(img) + 1);
figure, imshow(matEq)

%Complete based on prompts below (these are same as in Part 1)
%TODO 1: Compare with matlab's implementation.
[imEq, mapEq] = histeq(img, L); 

%TODO 2: Show both equalized images next to each other
figure, imshowpair(matEq, imEq, 'montage');

%TODO 3: Compute and print the Diff between homegrown and matlab (per pixel)
fprintf('Diff between homegrown and matlab implementation (per pixel) for file %s = %f\n',filename, sum(sum(abs(double(imEq) - double(matEq))))/(m*n));
