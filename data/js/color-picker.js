function colorPick() {
	return {
		isOn: window.isOn,
		h: window.hue,
		s: window.saturation,
		l: window.lightness,
		debounceTimer: null,

		// Convert HSV to RGB for display
		hsvToRgb(h, s, v) {
			h = h / 360;
			s = s / 100;
			v = v / 100;

			let r, g, b;
			let i = Math.floor(h * 6);
			let f = h * 6 - i;
			let p = v * (1 - s);
			let q = v * (1 - f * s);
			let t = v * (1 - (1 - f) * s);

			switch (i % 6) {
				case 0:
					(r = v), (g = t), (b = p);
					break;
				case 1:
					(r = q), (g = v), (b = p);
					break;
				case 2:
					(r = p), (g = v), (b = t);
					break;
				case 3:
					(r = p), (g = q), (b = v);
					break;
				case 4:
					(r = t), (g = p), (b = v);
					break;
				case 5:
					(r = v), (g = p), (b = q);
					break;
			}

			return `rgb(${Math.round(r * 255)}, ${Math.round(
				g * 255
			)}, ${Math.round(b * 255)})`;
		},

		async toggleLed() {
			await this.sendUpdate();
			console.log("Toggled LED power:", this.isOn ? "On" : "Off");
		},

		async handleSliderColorChange() {
			if (this.debounceTimer) clearTimeout(this.debounceTimer);

			this.debounceTimer = setTimeout(async () => {
				await this.sendUpdate();
				console.log("Changed the color!");
			}, 50);
		},

		async handleButtonColorChange(h, s, l) {
			this.h = h;
			this.s = s;
			this.l = l;
			await this.sendUpdate();
			console.log("Changed the color!");
		},
		// Normalize HSL values for ESP32
		// Converts: Hue (0-360) → (0-255), Saturation (0-100) → (0-255), Lightness (0-100) → (0-255)
		normalizeHslForEsp32(h, s, l) {
			return {
				h: Math.round((h / 360) * 255), // 0-360 → 0-255
				s: Math.round((s / 100) * 255), // 0-100 → 0-255
				l: Math.round((l / 100) * 255), // 0-100 → 0-255
			};
		},
		async sendUpdate(saveToSettings = false) {
			console.log("Applying settings:");
			console.log("LED Power:", this.isOn ? "On" : "Off");
			const normalizedHSL = this.normalizeHslForEsp32(
				this.h,
				this.s,
				this.l
			);

			console.log(normalizedHSL);

			// Send settings to the ESP32
			const ledState = this.isOn ? 1 : 0;
			let url = `${ENDPOINT.led}?ledState=${ledState}&h=${normalizedHSL.h}&s=${normalizedHSL.s}&l=${normalizedHSL.l}`;

			if (saveToSettings) {
				url += "&save=1";
			}

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
