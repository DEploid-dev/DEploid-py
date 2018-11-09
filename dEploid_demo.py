import dEploid

print("Hello from dEploid")
print("add: ", dEploid.add(3, 4))
print(dEploid.getLibraryVertionStr())
print(dEploid.getLassoLibraryVertionStr())
print(dEploid.getProgramVertionStr())
print(dEploid.getCompileTimeStr())

a = dEploid.VcfReaderPyType("lib/data/testData/PG0390-C.test.vcf")
a.get_refCount()
a.get_vcfheader()
a.get_altCount()

# print("add: ", dEploid.add(3, "4"))
