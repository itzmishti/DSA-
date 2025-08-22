Here’s a **structured summary in bullet points** of the entire discussion you shared:

---

### 1. **Adobe Data Layer Events**

* OnClick, OnLoad, OnChange events need to be **manually pushed** into the Adobe Data Layer.
* Application teams must explicitly add event scripts in their app code (not auto-captured).
* Example: When an onChange occurs, the app should also trigger a `window.adobeDataLayer.push()` event.

---

### 2. **Header Script Requirement**

* To capture events, a **header script** must be added in the app.
* If the application is hosted in **EXKit**, this script is already part of the global header → no need to add it separately.
* If the app is **not hosted in EXKit**, developers must include their own header script.

---

### 3. **Hybrid / Micro-frontend Applications**

* If an application is embedded inside another global app (with EXKit headers/footers), then the global script covers it.
* If running standalone (local dev, UAT, or test), the header script must be added manually, else `window.adobeDataLayer` will be undefined and events will fail.
* Workaround:

  * Add a **temporary header script** in lower environments.
  * Remove it when migrating to production under EXKit.

---

### 4. **Environment Scenarios**

* **Lower Environments (UAT, Dev, Test)**

  * App may run standalone without EXKit.
  * Developers need to include their own header script for event tracking.
* **Production (with EXKit)**

  * Header and footer provided globally.
  * No need for separate header script.
  * Events flow into Adobe Analytics global reports.

---

### 5. **EXKit vs Non-EXKit Applications**

* **EXKit Hosted**

  * Always uses `employee.<domain>` format in URL.
  * Has global header/footer by default.
  * No individual header script required.
* **Non-EXKit / Standalone**

  * Custom domain.
  * Needs explicit header script + manual Adobe Data Layer events.
* Data captured is the same in both cases → only implementation differs.

---

### 6. **Tracking Use Cases**

* Only **intranet applications** are supported (not external/public-facing apps).
* Session tracking stops once the user leaves the intranet domain.
* Applications can send Adobe Data Layer events for:

  * Page loads
  * Navigation
  * Click interactions
  * Surveys/feedback (if within intranet).

---

### 7. **Process for Defining Events**

* Teams provide the list of actions they want tracked.
* Adobe team provides a **template of standard events** (page load, clicks, navigation).
* If any custom use cases are missing, they will be mapped into existing event types.
* It’s a collaborative process → not one-way.

---

### 8. **Key Risks / Concerns**

* If events are added but the global script is missing, it will throw **console errors** and fail.
* Must ensure correct environment setup:

  * Temporary script for dev/UAT.
  * Global EXKit script for prod.

---

### 9. **Next Steps / Action Items**

* Confirm with Adobe team whether using different setups (custom script in UAT, EXKit script in prod) is acceptable.
* Adobe team to check internally with manager for feasibility and consistency across environments.
* Get contact details of another team who has already implemented Adobe Analytics with EXKit.
* Decide on a **pilot application** (Transport or Employee Listening) to implement first, learn from it, and reuse the approach across other apps.

---

✅ **In short:**

* Events must be coded manually (`window.adobeDataLayer.push`).
* Header script required → provided globally in EXKit, but must be added manually in non-EXKit apps.
* Lower environments will need temporary header scripts.
* Production in EXKit → global script takes over.
* Data is always sent to Adobe global reports, regardless of EXKit or non-EXKit.
* Pilot with one app (Transport/Employee Listening) before scaling to others.

---

Do you want me to also create a **visual flow diagram** showing how event capture works in **EXKit vs Non-EXKit environments**? That might make this easier to explain to your stakeholders.
