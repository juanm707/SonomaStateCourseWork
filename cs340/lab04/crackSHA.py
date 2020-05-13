import sys
from array import array
import base64
import hashlib
from time import time

# Make sure I was given all the inputs that I need (and no more)
if (len(sys.argv) != 3):
    print "Invalid syntax"
    sys.exit(1)

# open the password file and read in the contents
fd = open(sys.argv[1], 'r')
passes = fd.readlines()
fd.close()

# open the dictionary file and read in the contents
fd = open(sys.argv[2], 'r')
words = fd.readlines()
fd.close()

# Calc the number of lines in each file
num_passes = len(passes)
num_words  = len(words)

# Output some stats
print "-----------------------------"
print "Pre-processing of input data:"
print "-----------------------------"
print "Number of passwords = " + str(num_passes)
print "Number of words     = " + str(num_words)

# Extract the hashes from the password file for quicker comparisons
print "Extracting hashes from file"
hashes = []      # an array of the hashes
for line in passes:
    # Find where the braces are
    index1 = line.find('{')
    index2 = line.find('}')
    if (index1 <= 0) or (index2 <= 0):
        print "bad password file format"
        sys.exit(1)
    if (index2 <= index1):
        print "bad password file format"
        sys.exit(1)

    # Extract the algorithm and make sure it is SHA
    if ((line[index1+1:index2]) != "SHA"):
        print "Error: only input SHA1-based hashes"
        sys.exit(1)

    # Extract the hash, remove the trailing carriage return, and do the
    # Base64 decoding.
    hashes.append(base64.b64decode(line[index2+1:].strip('\n')))

# Now hash each word in the given dictionary and see if they match
# anything in the password file.
words_tried = 0
found = 0
print "-----------------------------"
print "Cracking..."
print "-----------------------------"
start_time = time()
for word in words:
    # 1. strip CR from word
    # 2. hash with SHA1
    words_tried = words_tried + 1
    newhash = hashlib.sha1(word.strip('\n')).digest()
    # print word.strip('\n') + " " + newhash

    # compare the new hash with every hash on file
    index = 0
    while (index < num_passes):
        if newhash == hashes[index]:
            # Extract user name from password entry
            name_index = passes[index].find(':')
            name = passes[index][:name_index]

            # Display the results
            print name + " password is '" + word.strip('\n') + "'"

            # increment our count
            found = found + 1
        index = index + 1
    if (found >= num_passes):
        break

stop_time = time()
total_time = stop_time - start_time
            
# Display statistics at the end
print "-----------------------------"
print "Found " + str(found) + " out of " + str(num_passes) + " passwords."
sys.stdout.write("Processed " + str(words_tried) + " words in ")
print str(round(total_time,3)) + " seconds."

