import dEploid

print("Hello from dEploid")
print("add: ", dEploid.add(3, 4))
print(dEploid.getLibraryVertionStr())
print(dEploid.getLassoLibraryVertionStr())
print(dEploid.getProgramVertionStr())
print(dEploid.getCompileTimeStr())

#dEploid.VcfReaderPyType("lib/data/testData/PG0390-C.test.vcf.gz")
a = dEploid.VcfReaderPyType("lib/data/testData/PG0390-C.test.vcf")

#print("add: ", dEploid.add(3, "4"))
