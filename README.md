# Sagerunex — The Long Way Out

An interactive, evidence-bounded malware-analysis case study built from the complete 37-section Sagerunex technical report and function map. The primary investigation contains 26 individually numbered leads—one for every challenge question—with a direct answer, technical reasoning, security significance, evidence target, caveat, and linked function record.

## Run

Serve the folder so staged and future decompiled functions can load in the viewer:

```powershell
python -m http.server 8000 --directory .
```

Then open `http://127.0.0.1:8000/`.

The page remains readable from `file://`, but browsers normally block local `fetch()` calls; the function viewer will explain that state rather than failing silently.

## Decompiled functions

All 31 supplied Ghidra functions are stored individually under `assets/decompiled/` and mapped to their viewer records. The source text is inert, and decompiler warnings, prototypes, and original symbols are preserved. Analyst-assigned display names live separately in `app.js`.

## Add screenshots later

The Evidence Capture Queue lists all 26 challenge figures in the revised collection plan. Screenshot assets were not supplied in this revision, so every slot is explicitly marked `AWAITING` rather than displaying fabricated evidence.

The authoritative source report is bundled at `assets/research/Sagerunex_Technical_Writeup.md` and linked from the verdict section. The distinct transfer-controller body cited for the 0xC000 `ReadFile` loop was not present in the supplied 31-function paste and remains an explicit evidence gap.

## Interaction and motion

The Function Atlas presents all 31 supplied function records as five horizontally scrollable execution lanes. The **Run execution trace** control animates a representative path from entry and identity handling through configuration, beaconing, routing, and command control; selecting any node opens its full supplied decompiler text as inert evidence.

The investigation cover and hero use the locally packaged `assets/images/sagerunex-dark-route-v2.png` artwork. Major reveals, route signals, hero copy, facts, and graph edges move left-to-right. Motion is disabled automatically when the browser requests reduced motion.

No executable sample, live command runner, persistence action, or network operation is included. All interactive demonstrations are visual models only.
