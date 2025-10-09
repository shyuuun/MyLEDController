function colorPick() {
	return {
		isOn: window.isOn,
		async applyColor() {
			console.log("Applying settings:");
			console.log("LED Power:", this.isOn ? "On" : "Off");
			console.log("Color:", this.color);

			// Send settings to the ESP32
			const ledState = this.isOn ? 1 : 0;
			const url = ENDPOINT.led;

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
