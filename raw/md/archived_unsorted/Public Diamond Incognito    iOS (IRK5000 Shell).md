
Ja — ich mache dir einen einzigen, vollständigen Output (ein „Frame“), ohne Ordnerstruktur, klar, technisch, menschenlesbar – und mit einem ausführbaren SwiftUI-Minimalprojekt als Single-File (du kopierst es in Xcode, es läuft).

  

Hinweis (Fakt): iOS braucht Xcode zum Bauen/Starten. „Ausführbar“ heißt hier: direkt lauffähig, sobald du die eine Datei in ein neues SwiftUI-App-Projekt einfügst.

  

  

  

# Public Diamond Incognito — iOS (IRK5000 Shell)

  

Status: public · minimal · deterministic · non-executing-by-default  

Kernel reference: IRK5000 (Kernel-adjacent, frozen-reference mindset)  

Role: iOS Shell = Viewer/Reader (read-only)

  

---

  

## 0) Was ist das?

  

**Public Diamond Incognito — iOS** ist eine **minimalistische iOS-Shell** für ein Frames-first System.

  

Sie macht genau drei Dinge:

  

1. **Frames lokal lesen** (JSON-Dateien im App-Speicher / Documents)

2. **Frames als Liste anzeigen** (Titel / ID / Status / Timestamp)

3. **Frame-Detail anzeigen** (strukturierte, menschenlesbare Ansicht)

  

Wichtig:

- **Kein Auto-Run**

- **Kein Auto-Send**

- **Kein Zurückschreiben**

- **Keine Interpretation jenseits der Struktur**

- **Keine Authority**

- **Kein Tracking**

  

Das ist eine Shell. Kein Produkt. Kein Netzwerk. Kein Push-System.

  

---

  

## 1) Kernprinzipien (kurz)

  

- Frames sind **Source of Truth**

- Translators / Viewers sind **optional**

- Meaning before interface

- Structure before features

- Longevity over speed

- No auto-run / No auto-send

- Read-only by default

  

---

  

## 2) Frame-Format (minimal, kompatibel)

  

Ein Frame ist eine JSON-Datei. Beispiel:

  

```json

{

  "id": "FRM-0001",

  "status": "active",

  "timestamp": "2026-01-01T00:00:00Z",

  "content": {

    "title": "Example Frame",

    "body": "This is a minimal unit of meaning."

  }

}

  

- id (String) — stabiler Identifier
- status (String) — z. B. active/frozen/draft
- timestamp (String) — ISO-8601 (optional)
- content (Object) — frei, aber human-verständlich

  

  

  

  

  

3) Wie du das startest (iPhone / iOS)

  

  

  

A) Xcode Start (empfohlen)

  

  

1. Xcode → New Project → iOS → App → Interface SwiftUI
2. Projektname z. B. PublicDiamondIncognito
3. Ersetze den Inhalt von PublicDiamondIncognitoApp.swift durch den Code unten (ein File).
4. Run.

  

  

  

B) Frames hinzufügen (lokal)

  

  

- Beim ersten Start erstellt die App einen Ordner frames im iOS Documents-Verzeichnis.
- Lege dort .json Frames ab:  
    

- via Finder (Device Files), oder
- via Files-App (wenn du File Sharing aktivierst), oder
- später via Share Sheet (nicht enthalten, bewusst minimal).

-   
    

  

  

Dann „Pull to refresh“ (oder App neu öffnen).

  

  

  

  

4) Der komplette, ausführbare Code (Single File)

  

  

Copy/Paste in ein SwiftUI-App-Projekt.

Das ist absichtlich klein, ruhig, ohne Abhängigkeiten.

import SwiftUI

  

// MARK: - Model

  

struct Frame: Codable, Identifiable, Hashable {

    let id: String

    let status: String?

    let timestamp: String?

    let content: [String: String]?

  

    // Fallback helpers (human-readable)

    var title: String {

        content?["title"] ?? id

    }

  

    var bodyText: String {

        content?["body"] ?? ""

    }

}

  

// MARK: - Storage (read-only, local)

  

enum FrameStoreError: Error {

    case invalidJSON

}

  

final class FrameStore: ObservableObject {

    @Published var frames: [Frame] = []

    @Published var lastLoadInfo: String = ""

  

    private let folderName = "frames"

  

    func ensureFramesFolderExists() {

        let folderURL = framesFolderURL()

        if !FileManager.default.fileExists(atPath: folderURL.path) {

            try? FileManager.default.createDirectory(at: folderURL, withIntermediateDirectories: true)

        }

    }

  

    func framesFolderURL() -> URL {

        let docs = FileManager.default.urls(for: .documentDirectory, in: .userDomainMask).first!

        return docs.appendingPathComponent(folderName, isDirectory: true)

    }

  

    func loadFrames() {

        ensureFramesFolderExists()

  

        let folderURL = framesFolderURL()

        let fm = FileManager.default

  

        let files: [URL]

        do {

            files = try fm.contentsOfDirectory(at: folderURL, includingPropertiesForKeys: nil)

                .filter { $0.pathExtension.lowercased() == "json" }

                .sorted { $0.lastPathComponent < $1.lastPathComponent }

        } catch {

            frames = []

            lastLoadInfo = "Failed to read frames folder."

            return

        }

  

        var loaded: [Frame] = []

        var ok = 0

        var bad = 0

  

        for url in files {

            do {

                let data = try Data(contentsOf: url)

                let frame = try JSONDecoder().decode(Frame.self, from: data)

                loaded.append(frame)

                ok += 1

            } catch {

                bad += 1

                continue

            }

        }

  

        // Deterministic sort: timestamp (desc) then id (asc)

        loaded.sort {

            let t0 = $0.timestamp ?? ""

            let t1 = $1.timestamp ?? ""

            if t0 != t1 { return t0 > t1 }

            return $0.id < $1.id

        }

  

        frames = loaded

        lastLoadInfo = "Loaded \(ok) frame(s). \(bad) invalid."

    }

  

    func seedExampleFrameIfEmpty() {

        ensureFramesFolderExists()

        let folderURL = framesFolderURL()

        let fm = FileManager.default

  

        let existing = (try? fm.contentsOfDirectory(at: folderURL, includingPropertiesForKeys: nil)) ?? []

        if existing.contains(where: { $0.pathExtension.lowercased() == "json" }) { return }

  

        let example = """

        {

          "id": "FRM-0001",

          "status": "active",

          "timestamp": "2026-01-01T00:00:00Z",

          "content": {

            "title": "Example Frame",

            "body": "This is a minimal unit of meaning."

          }

        }

        """

  

        let url = folderURL.appendingPathComponent("FRM-0001.json")

        try? example.data(using: .utf8)?.write(to: url, options: [.atomic])

    }

}

  

// MARK: - UI

  

struct ContentView: View {

    @StateObject private var store = FrameStore()

  

    var body: some View {

        NavigationStack {

            List(store.frames) { frame in

                NavigationLink(value: frame) {

                    VStack(alignment: .leading, spacing: 6) {

                        Text(frame.title)

                            .font(.headline)

                            .lineLimit(1)

  

                        HStack(spacing: 10) {

                            Text(frame.id)

                                .font(.caption)

                                .foregroundStyle(.secondary)

  

                            if let status = frame.status, !status.isEmpty {

                                Text(status)

                                    .font(.caption)

                                    .foregroundStyle(.secondary)

                            }

  

                            Spacer()

  

                            if let ts = frame.timestamp, !ts.isEmpty {

                                Text(ts)

                                    .font(.caption)

                                    .foregroundStyle(.secondary)

                                    .lineLimit(1)

                            }

                        }

                    }

                    .padding(.vertical, 4)

                }

            }

            .navigationTitle("Diamond Incognito")

            .toolbar {

                ToolbarItem(placement: .topBarTrailing) {

                    Button("Reload") { store.loadFrames() }

                }

            }

            .refreshable {

                store.loadFrames()

            }

            .navigationDestination(for: Frame.self) { frame in

                FrameDetailView(frame: frame, folderURL: store.framesFolderURL())

            }

            .safeAreaInset(edge: .bottom) {

                StatusBar(text: store.lastLoadInfo)

            }

        }

        .onAppear {

            // First-run: create folder + seed an example frame (safe, local, deterministic)

            store.seedExampleFrameIfEmpty()

            store.loadFrames()

        }

    }

}

  

struct FrameDetailView: View {

    let frame: Frame

    let folderURL: URL

  

    var body: some View {

        ScrollView {

            VStack(alignment: .leading, spacing: 14) {

                Group {

                    Text(frame.title).font(.title2).bold()

                    KeyValueRow(key: "Frame ID", value: frame.id)

                    KeyValueRow(key: "Status", value: frame.status ?? "—")

                    KeyValueRow(key: "Timestamp", value: frame.timestamp ?? "—")

                    KeyValueRow(key: "Folder", value: folderURL.lastPathComponent)

                }

  

                Divider()

  

                Text("Content").font(.headline)

                if let content = frame.content, !content.isEmpty {

                    ForEach(content.keys.sorted(), id: \.self) { k in

                        KeyValueRow(key: k, value: content[k] ?? "")

                    }

                } else {

                    Text("—").foregroundStyle(.secondary)

                }

  

                if !frame.bodyText.isEmpty {

                    Divider()

                    Text("Body").font(.headline)

                    Text(frame.bodyText)

                        .font(.body)

                        .foregroundStyle(.primary)

                }

            }

            .padding(16)

        }

        .navigationTitle("Frame")

        .navigationBarTitleDisplayMode(.inline)

    }

}

  

struct KeyValueRow: View {

    let key: String

    let value: String

  

    var body: some View {

        VStack(alignment: .leading, spacing: 4) {

            Text(key)

                .font(.caption)

                .foregroundStyle(.secondary)

            Text(value.isEmpty ? "—" : value)

                .font(.body)

                .textSelection(.enabled)

        }

    }

}

  

struct StatusBar: View {

    let text: String

    var body: some View {

        if text.isEmpty { EmptyView() }

        else {

            VStack(spacing: 0) {

                Divider()

                HStack {

                    Text(text)

                        .font(.caption)

                        .foregroundStyle(.secondary)

                        .lineLimit(1)

                    Spacer()

                }

                .padding(.horizontal, 12)

                .padding(.vertical, 10)

                .background(.ultraThinMaterial)

            }

        }

    }

}

  

// MARK: - App Entry

  

@main

struct PublicDiamondIncognitoApp: App {

    var body: some Scene {

        WindowGroup {

            ContentView()

        }

    }

}

  

  

  

  

5) Sicherheits- und Grenzen-Hinweis (technisch, klar)

  

  

Diese iOS Shell:

  

- liest nur lokale JSON-Dateien
- sendet nichts
- schreibt nichts zurück
- hat keine Hintergrund-Tasks
- ist nicht „Kernel“, nur Viewer

  

  

  

  

  

6) Lizenz

  

  

MIT — do what you want, but know what you are doing.

  

  

  

End of single-file output.

Wenn du als nächstes willst, mache ich dir **denselben Output** nochmal als *noch kürzeres* „Public Release Frame“ (weniger Text, mehr Essenz) – oder wir bauen eine **manuelle Import-Funktion** (Share Sheet / Files) rein, ebenfalls ohne Auto-Send.