# Build Instructions for FakeGDMod

## Prerequisites

Before building, you need:

1. ✅ **Geode CLI** - Located at `C:\Users\zekef\Downloads\gdsdk\geode.exe`
2. ❌ **CMake** - Not yet installed (required!)
3. ⚠️ **Visual Studio Build Tools** - Recommended for Windows

## Quick Setup

### Step 1: Install CMake

**Option A: MSI Installer (Recommended)**
1. Download from: https://cmake.org/download/
2. Get: `cmake-3.28.x-windows-x86_64.msi`
3. Run installer
4. **IMPORTANT:** Check "Add CMake to system PATH for all users"
5. Click through to finish

**Option B: Portable ZIP**
1. Download: `cmake-3.28.x-windows-x86_64.zip`
2. Extract to `C:\cmake`
3. Add `C:\cmake\bin` to your PATH manually

### Step 2: Verify Installation

Open a **new** PowerShell window and run:
```powershell
cmake --version
```

You should see: `cmake version 3.28.x` (or higher)

### Step 3: Build the Mod

**Option A: Use the build script**
```batch
build.bat
```

**Option B: Command line**
```powershell
C:\Users\zekef\Downloads\gdsdk\geode.exe build
```

## Expected Output

If successful, you'll see:
```
| Success | Successfully built package
```

The compiled mod will be at:
```
C:\Users\zekef\Downloads\FakeGDMod-master\build\FakeGDMod.geode
```

## Installing Your Mod

1. Copy `FakeGDMod.geode` from the `build` folder
2. Paste it into your Geometry Dash mods folder:
   - Usually: `%LOCALAPPDATA%\GeometryDash\geode\mods\`
3. Launch Geometry Dash
4. The mod will load automatically!

## Troubleshooting

### "cmake not found"
- Install CMake (see Step 1 above)
- Restart PowerShell/Command Prompt
- Make sure it's in your PATH

### "Visual Studio not found"
Install Visual Studio Build Tools:
- Download: https://visualstudio.microsoft.com/downloads/
- Get: "Build Tools for Visual Studio 2022"
- Install "Desktop development with C++"

### "GEODE_SDK not found"
The Geode CLI should handle this automatically. If not:
```powershell
$env:GEODE_SDK = "C:\Users\zekef\Downloads\gdsdk"
```

### Still having issues?
Check the [Geode Documentation](https://docs.geode-sdk.org/getting-started/)

## What You're Building

This mod includes:
- 🎛️ Custom Moderator Control Panel (8 features)
- 👤 4 role types (Mod, Elder, LB Mod, Developer)
- 📋 Reported levels browser
- 🔍 User search system
- 📊 Statistics dashboard
- 🛠️ Complete moderation toolkit
- And 20+ more features!

Total: **1000+ lines of professional C++ code**

---

**Ready to build?** Just install CMake and run `build.bat`!
