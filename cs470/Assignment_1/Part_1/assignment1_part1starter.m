%% Load image
%Example image filenames below are among the images shown in textbook (Alasdair McAndrew).
%You need to add them to the path using Set Path option from the main Matlab window

filename = 'engineer.png';
%filename = 'cameraman.png'; 
%filename = 'bergen.jpg';

L = 256; %Number of gray-levels we will be dealing with

% TODO: Read the image and store into variable img 
img = imread(filename);
figure, imshow(img)
%% Home-grown histogram: Create a histogram without using Matlab's toolbox
% mat = Initialize a vector of size L (because there are L gray-values) to all zeros. This will subsequently store the histogram.
mat = zeros(L,1);
%Loop over the pixels in image. 
%Note: size(img) returns width and height of the image

%TODO: Enter code here
[w, h] = size(img);
%loop index i iterates over rows
for i = 1:w
   %loop index j iterates over columns
   for j = 1:h
          gray = img(i,j); %value between 0 and 255
          %Now, increment mat for the grayvalue "gray"
          %While incrementing, keep in mind that index of matrices in
          %Matlab starts from 1 but gray value can be 0. Secondly, if img is
          %of type uint8, then it can't store values above 255.
          %TODO: Enter code here
          gray = double(gray) + 1;
          mat(gray) = mat(gray) + 1;              
    %end loop columns
   end
%end loop rows
end

%
hist = imhist(img); %Matlab's implementation of histogram
%Compare with matlab's implementation..they should be exactly same. 
%TODO: Run and check output for all the different filenames in first section above - they all should return 0
fprintf('Diff hist = %d\n',sum(sum(abs(double(hist) - double(mat))))); 

%If not same, why? Debug by storing the difference (hist-mat) in a
%variable and checking where they are different


%% Home-grown cumulative histogram: Create a cumulative histogram without using Matlab's toolbox
matc = zeros(L, 1); %Initialize a vector of size L (because there are L gray-values). This will store the cumulative histogram.

%Recall, Histogram is stored in variable mat. 
%Use the formula of cumulative histogram to update matc. c_{i+1} = c_{i} + n_i+1
matc(1)=mat(1);
%TODO: Enter code here 
[s, ~] = size(mat);
for i = 1:s-1
    matc(i+1) = matc(i) + mat(i+1);
end

histc = cumsum(hist); %Compare with matlab's implementation.. are they exactly same? They should be...
fprintf('Diff cumulative hist = %d\n',sum(sum(abs(double(histc) - double(matc)))));


%% Home-grown histogram equalization: Perform histogram equalization without using Matlab's toolbox
map = zeros(L,1,'uint8'); %This will store the transformation. Specifying the type uint8 ensures that the transform doesn't go out of bounds [0, 255]

%n = Total number of pixels
n = size(img,1)*size(img,2);

%Apply formula matc(i)*(L-1)/n to populate the values in map.
%TODO: Enter code here

%map = uint8(matc * ((L - 1)/n)); 
%map = uint8((matc/n) * (L - 1));
[sr, ~] = size(map);
for i=1:sr
    map(i) = matc(i)*(L-1)/n;
end

%Apply the map to the image (i.e. Transform the pixels in img based on the transformation stored in map).
%Section 4.4 of the textbook shows a compact syntax for doing this: matEq = map(img)
%But what should be really  provided as the parameter? Recall that img is of type uint8. And Matlab's indexing begins from 1 (not 0)
%TODO: FIX code in the next line
matEq = map(double(img) + 1);

%Compare with matlab's implementation.
%Default implementation of histeq outputs 64 discrete graylevels (from Matlab help). But our home-grown version uses 256. 
%TODO: FIX the code in the next line so that histeq used 256 discrete graylevels
[imEq, mapEq] = histeq(img, 256); 

%Show both equalized images next to each other
figure, imshowpair(matEq, imEq, 'montage');

%Because Matlab uses a slightly different algorithm, the difference per
%pixel (see below) will not be zero but a very small value 
fprintf('Diff between homegrown and matlab implementation (per pixel) for file %s = %f\n',filename, sum(sum(abs(double(imEq) - double(matEq))))/n);

