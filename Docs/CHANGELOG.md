# Changelog

## v0.2 — Expanded Build
Added on top of the v0.1 foundation, with real (non-stub) logic:
- Maritime Traffic Simulation + trade routes (`Source/BlackOcean/Traffic`)
- Global Maritime Market: supply/demand-driven commodity pricing (`Economy/GlobalMarketSubsystem`)
- Weather Forecast System: probabilistic, technology-gated, confidence-scored (`Ocean/WeatherForecastSubsystem`)
- Dynamic Difficulty as multi-axis settings (info quality, severity, scarcity, AI coordination, complexity), not just health/damage (`Core/DifficultySettings`)
- Achievements System (`Meta/AchievementsSubsystem`)
- Commander Progression with gameplay-scoped perks (`Meta/CommanderProgression`)
- Environmental System: pollution, temperature anomaly, wildlife density, protected areas (`Environment/EnvironmentalSubsystem`)
- Admiralty/Command Center with upgradeable facilities (`Command/AdmiraltyCommandCenter`)
- Fleet Customization: colors, emblem, naming (cosmetic only) (`Fleet/FleetCustomization`)
- Simulation Inspector: generic entity snapshot registry for debug/design UI (`Simulation/SimulationInspectorSubsystem`)
- Fleet Chronicle: human-readable long-term campaign history, distinct from the low-level replay stream (`Replay/FleetChronicleSubsystem`)
- Performance Profiler subsystem for the design spec's named cost categories (AI/Physics/Ocean/Streaming/Simulation/Network) (`Tools/PerformanceProfilerSubsystem`)
- Mod Manifest + compatibility validation (`Tools/ModManifest`)
- Theme- and localization-aware UMG widget base class (`UI/BlackOceanWidgetBase`)
- Photo Mode component (`UI/PhotoModeComponent`)
- GitHub Actions CI workflow for a self-hosted Windows/UE5 runner (`.github/workflows/windows-ci.yml`)
- Sample Data Table CSVs for ship classes and research nodes (`Content/Data/`)
- Additional automation tests: sensor fusion decay/corroboration, economy budget allocation (`Tests/`)

## v0.1 — Initial Foundation
Core module scaffold: Core, Simulation, Ocean, Ships, Submarine, AirAssets,
Crew, Sensors, Navigation, Fleet, Command, AI, Logistics, Ports (incl.
player-configurable operating hours), Shipyard, Research, Economy,
Diplomacy, Missions, Dialogue, Save, Replay, UI (themes + localization),
Networking (interfaces only), Tools. Windows build/test/package scripts,
INSTALLATION.md, and this trilingual README.
