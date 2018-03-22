$fname = "script"

if ($args[0] -eq "clean")
{
#ECHO 'Versuche Dateien zu löschen, sofern sie vorhanden sind:'
try {
del (-join($fname,'.aux'))
}
finally {}
try {
del (-join($fname,'.listing'))
}
finally {}
try {
del (-join($fname,'.log'))
}
finally {}
try {
del (-join($fname,'.out'))
}
finally {}
try {
del (-join($fname,'.rai'))
}
finally {}
try {
del (-join($fname,'.rao'))
}
finally {}
try {
del (-join($fname,'.synctex.gz'))
}
finally {}
try {
del (-join($fname,'.toc'))
}
finally {}
}

if ($args[0] -eq "rail")
{
rail $fname
}