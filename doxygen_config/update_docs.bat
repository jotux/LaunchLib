doxygen ./doxy_launchlib
cd ..
xcopy .\docs ..\docs /s /i
git checkout gh-pages
rmdir .\docs /s /q
xcopy ..\docs .\docs /s /i
rmdir ..\docs /s /q
git add -u
git add .
git commit -m "Automatic doc update"
git push