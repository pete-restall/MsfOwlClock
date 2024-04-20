function mm(x) = x;

module ferriteRod(length, diameter) {
	color("#000000")
		rotate([0, 90, 0])
		difference() {
			radius = diameter / 2;
			translate([0, 0, -length / 2])
				linear_extrude(length)
				circle(d=diameter, $fn=360);

			translate([0, radius, 0])
				cube([diameter, mm(2), length + 1], center=true);

			translate([0, -radius, 0])
				cube([diameter, mm(2), length + 1], center=true);
		}
}

module copperLoop(loopDiameter, wireDiameter) {
	color("#f7703b")
		rotate([0, 90, 0])
		rotate_extrude(convexity=10, $fn=10)
		translate([loopDiameter / 2 + wireDiameter, 0, 0])
			circle(r=wireDiameter, $fn=10);
}

module copperLoops(turns) {
	wireDiameter = mm(0.5);
	halfLength = wireDiameter * (turns / 2);
	for (x = [-halfLength : wireDiameter : halfLength]) {
		translate([x, 0, 0])
			copperLoop(loopDiameter=mm(10), wireDiameter=wireDiameter);
	}
}

ferriteRod(length=mm(100), diameter=mm(10));
//copperLoops(turns=164);
