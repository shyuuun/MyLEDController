function colorPick() {
	return {
		isOn: window.isOn,
		r: window.red,
		g: window.green,
		b: window.blue,
		debounceTimer: null,

		async toggleLed() {
			await this.sendUpdate();
			console.log("Toggled LED power:", this.isOn ? "On" : "Off");
		},

		async applyColor() {
			if (this.debounceTimer) clearTimeout(this.debounceTimer);

			this.debounceTimer = setTimeout(async () => {
				await this.sendUpdate();
				console.log("Changed the color!");
			}, 50);
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
