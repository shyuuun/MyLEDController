function colorPick() {
	return {
		isOn: false,
		color: "#ff0000",
		brightness: 128,

		async applyColor() {
			console.log("Applying settings:");
			console.log("LED Power:", this.isOn ? "On" : "Off");
			console.log("Color:", this.color);
			console.log("Brightness:", this.brightness);
			// Here you would typically send the settings to your backend or device

			fetch("/led");
		},
	};
}
