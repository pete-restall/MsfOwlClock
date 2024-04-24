function mm(x) = x;

module tiewrapFlatHalfLoop(loopInnerDiameter, tiewrapThickness) {
	loopOuterDiameter = loopInnerDiameter + tiewrapThickness * 2;
	loopOuterRadius = loopOuterDiameter / 2;
	difference() {
		circle(d=loopOuterDiameter, $fn=60);

		circle(d=loopInnerDiameter, $fn=60);

		translate([0, loopOuterRadius, 0])
			square([loopOuterDiameter, loopOuterDiameter], center=true);
	}
}

module tiewrapFlat(loopInnerDiameter, loopStretch, tiewrapThickness) {
	loopOuterDiameter = loopInnerDiameter + tiewrapThickness * 2;
	loopOuterRadius = loopOuterDiameter / 2;
	loopInnerRadius = loopInnerDiameter / 2;
	union() {
		translate([0, -loopStretch / 2, 0])
		tiewrapFlatHalfLoop(loopInnerDiameter, tiewrapThickness);

		translate([0, loopStretch / 2, 0])
			rotate([0, 0, 180])
			tiewrapFlatHalfLoop(loopInnerDiameter, tiewrapThickness);

		translate([loopInnerRadius + tiewrapThickness / 2, 0, 0])
			square([tiewrapThickness, loopStretch], center=true);

		translate([-loopInnerRadius - tiewrapThickness / 2, 0, 0])
			square([tiewrapThickness, loopStretch], center=true);
	}
}

module tiewrapLoop(loopInnerDiameter, loopStretch, tiewrapWidth, tiewrapThickness) {
	lockDepth = mm(2);
	lockHeight = mm(2);
	color("#ffff00")
		union() {
			translate([0, loopInnerDiameter / 2 + tiewrapThickness + loopStretch / 2	 + (lockDepth - tiewrapThickness) / 2, 0])
				cube([tiewrapWidth, lockDepth + tiewrapThickness / 2, lockHeight], center=true);

			rotate([0, 90, 0])
				linear_extrude(tiewrapWidth, center=true)
				tiewrapFlat(loopInnerDiameter, loopStretch, tiewrapThickness);
		}
}

for (x = [ -mm(7.5) : mm(7.5) : mm(7.5) ]) {
	translate([x, 0, 0])
		tiewrapLoop(loopInnerDiameter=mm(11), loopStretch=mm(1.6 + 12 / 2), tiewrapWidth=mm(2.5), tiewrapThickness=mm(1.25));
}
