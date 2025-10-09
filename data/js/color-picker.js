function colorPick() {
	return {
		isOn: window.isOn,
		color: window.ledColor,
		brightness: window.brightness,

		async applyColor() {
			console.log("Applying settings:");
			console.log("LED Power:", this.isOn ? "On" : "Off");
			console.log("Color:", this.color);
			console.log("Brightness:", this.brightness);

			// Send settings to the ESP32
			const ledState = this.isOn ? 1 : 0;
			const url = `/led?ledState=${ledState}&brightness=${
				this.brightness
			}&ledColor=${encodeURIComponent(this.color)}`;

			try {
				const response = await fetch(url);
				if (response.ok) {
					console.log("Settings applied successfully!");
				} else {
					console.error(
						"Failed to apply settings:",
						response.statusText
					);
				}
			} catch (error) {
				console.error("Error applying settings:", error);
			}
		},
	};
}
