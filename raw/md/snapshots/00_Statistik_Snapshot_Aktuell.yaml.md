platform:
  name: spotify

snapshot:
  date: YYYY-MM-DD
  type: statistics
  scope: current_state

metrics:
  impressions_total: null
  streams_total: null
  followers_total: null

source:
  provider: spotify_for_podcasters
  method: manual_entry

references:
  vault_path: "01_Fakten/Statistiken/Spotify/00_Statistik_Snapshot_Aktuell.md"
  platform:
    vault_path: "01_Fakten/Plattformen/Spotify.md"
  project_snapshot:
    vault_path: "01_Fakten/Snapshots/00_Projekt_Snapshot_Aktuell.md"

notes:
  - "Erster Statistik-Snapshot ohne Verlauf"