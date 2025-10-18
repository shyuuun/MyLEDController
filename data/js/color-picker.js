function colorPick() {
	return {
		isOn: window.isOn,
		r: window.red,
		g: window.green,
		b: window.blue,
		debounceTimer: null,

		async applyColor() {
			if (this.debounceTimer) {
				clearTimeout(this.debounceTimer);
			}

			this.debounceTimer = setTimeout(() => {
				this.sendUpdate();
			}, 250);

			console.log("Changed the color!");
		},

		async sendUpdate() {
			console.log("Applying settings:");
			console.log("LED Power:", this.isOn ? "On" : "Off");
			console.log("RGB:", this.r, this.g, this.b);
			// Send settings to the ESP32
			const ledState = this.isOn ? 1 : 0;
			const url = `${ENDPOINT.led}?ledState=${ledState}&r=${this.r}&g=${this.g}&b=${this.b}`;
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
