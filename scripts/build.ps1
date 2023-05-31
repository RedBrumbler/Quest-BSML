Param(
    [Parameter(Mandatory=$false)]
    [Switch]$clean,
    [Parameter(Mandatory=$false)]
    [Switch]$docs
)

# if user specified clean, remove all build files
if ($clean.IsPresent)
{
    if (Test-Path -Path "build")
    {
        remove-item build -R
    }
}

if (($clean.IsPresent) -or (-not (Test-Path -Path "build")))
{
    new-item -Path build -ItemType Directory
}

$make_docs = "-DMAKE_DOCS=" + $docs.IsPresent.ToString().ToLower()

& cmake -G "Ninja" -DCMAKE_BUILD_TYPE="Debug" $make_docs . -B build 
& cmake --build ./build

exit $LastExitCode