#run from the root project folder
#pass no arguments if ALL icons are to be copied
#pass 1 argument with name of png file (without extension) if only that icon is to be copied

if [ $# -eq 1 ]; then
echo "copying just $1 icon"
file=$1; echo $file; cp build/Android/res/drawable-mdpi/$file.png resources/iOS/Icons/$file.png; cp build/Android/res/drawable-hdpi/$file.png resources/iOS/Icons/$file~ipad.png; cp build/Android/res/drawable-xhdpi/$file.png resources/iOS/Icons/$file@2x.png; cp build/Android/res/drawable-xxhdpi/$file.png resources/iOS/Icons/$file@2x~ipad.png; cp build/Android/res/drawable-xxxhdpi/$file.png resources/iOS/Icons/$file@3x.png;
else
echo "copying ALL icons"
for i in `ls build/Android/res/drawable-mdpi/`; do file=`echo $i | cut -d'.' -f1`; echo $file; cp build/Android/res/drawable-mdpi/$file.png resources/iOS/Icons/$file.png; cp build/Android/res/drawable-hdpi/$file.png resources/iOS/Icons/$file~ipad.png; cp build/Android/res/drawable-xhdpi/$file.png resources/iOS/Icons/$file@2x.png; cp build/Android/res/drawable-xxhdpi/$file.png resources/iOS/Icons/$file@2x~ipad.png; cp build/Android/res/drawable-xxxhdpi/$file.png resources/iOS/Icons/$file@3x.png; done
fi
