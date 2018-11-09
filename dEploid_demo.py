import dEploid
from matplotlib import pyplot

print("Hello from dEploid")
print("add: ", dEploid.add(3, 4))
print(dEploid.getLibraryVertionStr())
print(dEploid.getLassoLibraryVertionStr())
print(dEploid.getProgramVertionStr())
print(dEploid.getCompileTimeStr())

a = dEploid.Vcf("lib/data/exampleData/PG0390-C.eg.vcf.gz")

a.get_vcfheader()

ref = a.get_refCount()
alt = a.get_altCount()

count_max = max(max(ref), max(alt))
pyplot.scatter(ref, alt, c=a.get_vqslod())
pyplot.xlim(0, 0.9*count_max)
pyplot.ylim(0, 0.9*count_max)
pyplot.savefig("altVsRef.png", dpi=72)
pyplot.close('all')
