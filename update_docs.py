from subprocess import call
import shutil

call(["doxygen", "./doxy_launchlib"])
shutil.copytree(".\docs", "..\docs")
shutil.rmtree(".\docs")
call(["git","checkout","gh-pages"])
shutil.rmtree(".\docs")
shutil.copytree("..\docs", ".\docs")
shutil.rmtree("..\docs")
call(["git","add","-u"])
call(["git","add","."])
call(["git","commit","-m","Automatic doc update"])