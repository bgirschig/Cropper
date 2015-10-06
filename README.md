# Cropper

The cropper class can be used to select a region of interest and crop / scale it to fit in a target region.

## Basic use:
```cpp
void ofApp::draw(){
  myCropper.setSource(0,0,200,200);   // the cropper will select an area of 200x200px at the top left...
  myCropper.setFitMode(STRETCH);      // ... then stretch it in ...
  myCropper.setTarget(0,0,300,100);   // ... an area of 300x100px

  myCropper.begin();
  // here, draw stuff that will be transformed, scaled and cropped by the cropper
  myCropper.end();
  
  myCropper.draw();
}
```


## Fitmodes
There are three fit modes:
- FIT: Makes the source zone fit in the target one (while keeping ratio)
- FILL: Makes the source zone cover the target zone (while keeping ratio)
- STRETCH: Does not care about ratio, stretches the source onto the target

## AlignModes
In the FIT and FILL mode, part of the selected source will have to be cropped.
By default, the source is centered inside the target, but it can be placed at the
top-left, bottom-center...
Using this function:
```cpp
	myCropper.setAlignMode(TOP_LEFT);
```

Available align modes:
- TOP_LEFT
- TOP_CENTER
- TOP_RIGHT
- CENTER_LEFT
- CENTER
- CENTER_RIGHT
- BOTTOM_LEFT
- BOTTOM_CENTER
- BOTTOM_RIGHT