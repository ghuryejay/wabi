import sys
import os

def main():
        #fasta_file = sys.argv[1]
        repeat_file = sys.argv[1]
        #f_file = open(fasta_file,"rb")
        r_file = open(repeat_file,"rb")
        param = sys.argv[2]
        map_file = sys.argv[3]
	rt_file = sys.argv[4]
	rep_map = {}
	mf = open(map_file,"rb")
	lines = mf.readlines()
	for line in lines:
		attrs = line.split("\t")
		rep_map[attrs[0]] = int(attrs[1][:-1])
	'''
	genome_map = {}
        lines = f_file.readlines()
        key = ""
        for line in lines:
                line = line[:-1]
                if line[0] == '>':
                        key = line
                else:
                        genome_map[key] = line
        '''
	false_positive = 0
        true_positive = 0
        true_negative = 0
        false_negative = 0
        lines = r_file.readlines()
        revcompl = lambda x: ''.join([{'A':'T','C':'G','G':'C','T':'A'}[B] for B in x][::-1])
        for line in lines:
                attrs = line.split("\t")
                label = attrs[2]
                isrepeat = int(attrs[-1][:-1])
                label = label.strip("\"")
                cnt = 0
		
		cnt += rep_map[label]
#		if revcompl(label) in rep_map:	
   #             	cnt += rep_map[revcompl(label)]
		
                if cnt > 1 and isrepeat == 1:
                        true_positive += 1
                if cnt > 1 and isrepeat == 0:
                        false_negative += 1
                if cnt == 1 and isrepeat == 1:
                        false_positive += 1
                if cnt == 1 and isrepeat == 0:
                        true_negative += 1

        runfile = open(rt_file,"rb")
        line = runfile.readline()
      	# print order nodes/epsilon       runtime true_pos        true_neg        false_pos       false_neg       
        line = line.strip("\n")
	print str(param) + "\t" + line + "\t" + str(true_positive) + "\t" + str(true_negative) + "\t" + str(false_positive) + "\t" + str(false_negative)
        os.remove(rt_file)



if __name__ == "__main__":
        main()

