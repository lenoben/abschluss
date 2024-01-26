#!/usr/bin/python3

import argparse
import gzip
import simplejson

# Create the parser
parser = argparse.ArgumentParser()

# Add the arguments
parser.add_argument('inputFile', help='The complete or relative inputfile path')
parser.add_argument('outputFile', help='The complete or relative outputfile path')

# Parse the arguments
args = parser.parse_args()


def parse(filename):
    with gzip.open(filename, 'rb') as f:
        entry = {}
        for line_bytes in f:
            line = line_bytes.decode('utf-8').strip()
            colonPos = line.find(':')
            if colonPos == -1:
                yield entry
                entry = {}
                continue
            eName = line[:colonPos]
            rest = line[colonPos + 2:]
            entry[eName] = rest
        yield entry

def convert(input_file, output_file):
    # Open the output file in write mode
    with open(output_file, 'w') as out_file:
        for e in parse(input_file):
            json_data = simplejson.dumps(e)
            out_file.write(json_data + '\n')

    print("Data from '{}' saved to '{}'.".format(input_file, output_file))

# Entry
convert(args.inputFile,args.outputFile)