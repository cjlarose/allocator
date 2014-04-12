import sys

if len(sys.argv) < 2:
    print "[%s]" % ("."*50)
else:
    so_far = int(sys.argv[1])
    total = int(sys.argv[2])
    percent = int(float(so_far) / (total+1) * 100 / 2)
    print "[%-50s] (%d/%d)" % ("."*percent, so_far, total)
