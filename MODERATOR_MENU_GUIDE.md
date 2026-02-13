# Moderator Control Panel - Complete Guide

## 🎛️ Overview

The **Moderator Control Panel** is a comprehensive dashboard that gives you centralized access to all moderator features and tools. This custom interface simulates a real moderator management system with authentic features and professional design.

## 🚀 Accessing the Control Panel

### Location
- **Main Menu Button**: Look for the moderator badge icon in the bottom-right corner of the main menu
- **Notification Badge**: Shows the number of pending reports (randomly generated)
- **Availability**: Only appears for users with Moderator role or higher (Role 1-4)

### Opening
1. Launch Geometry Dash
2. Wait for main menu to load
3. Click the moderator badge button (bottom-right)
4. The control panel will animate in with an elastic effect

## 📋 Control Panel Features

### 1. 📂 Reported Levels
**What it does:** Browse levels that have been reported by the community

**Simulation:**
- Navigates to random unrated levels (simulating reported content)
- Shows loading animation: "Loading reported levels..."
- Displays notification: "Viewing reported levels for review"
- Opens Level Browser with unrated level filter

**Use case:** Review content that users have flagged for moderation

---

### 2. 🔍 User Search
**What it does:** Search for any user to view moderation options

**Features:**
- Input dialog prompts for username
- Loading animation: "Searching for user '[username]'..."
- Displays user profile card with:
  - Pending reports count (1-5, randomized)
  - Account status (Active)
  - User ID (randomly generated)
  - Available actions list

**Available Actions:**
- Ban/Unban User
- View Reports
- Reset Progress
- Send Message

**Use case:** Look up specific users for moderation actions

---

### 3. 📊 Level Queue
**What it does:** View levels awaiting moderation and rating

**Simulation:**
- Shows loading: "Loading level moderation queue..."
- Navigates to "Most Recent" levels
- Success notification: "Level moderation queue loaded"

**Use case:** Browse newly uploaded levels that need rating/featuring

---

### 4. 📈 Mod Stats
**What it does:** Display your personal moderation statistics

**Statistics Shown:**
- **Levels Rated:** 10-999 (randomized)
- **Levels Featured:** 1-99 (randomized)
- **Epic Levels:** 0-49 (randomized)
- **Comments Deleted:** 2-199 (randomized)
- **Users Moderated:** 0-66 (randomized)

**Features:**
- Color-coded statistics display
- Motivational message: "Keep up the great work!"
- Professional formatting with icons

**Use case:** Track your moderation activity and contributions

---

### 5. 🚫 Ban/Unban User
**What it does:** Simulate banning or unbanning users

**Process:**
1. Click the button
2. Enter username or ID in input dialog
3. Loading animation: "Processing ban request..."
4. Random outcome:
   - **Ban:** "User has been BANNED - Terms of Service violation"
   - **Unban:** "User has been UNBANNED - They can now access the game"

**Use case:** Moderate users who violate community guidelines

---

### 6. 📝 View Reports
**What it does:** Display comprehensive report statistics

**Dashboard Metrics:**
- **Total Reports:** 5-50 (randomized)
- **Level Reports:** Subset of total
- **User Reports:** Subset of total
- **Comment Reports:** Subset of total
- **Priority Level:** High
- **Action Required:** Random count

**Features:**
- Color-coded report types
- Priority indicator
- Summary statistics

**Use case:** Get an overview of all pending moderation reports

---

### 7. 🛠️ Mod Tools
**What it does:** Display available moderator utilities

**Tools Listed:**
- **Mass Level Action** - Batch operations on multiple levels
- **Batch User Moderation** - Moderate multiple users at once
- **Comment Filter Editor** - Customize comment filtering rules
- **Auto-Moderation Rules** - Set up automated moderation
- **Report Analytics** - Detailed report statistics and trends
- **Content Scanner** - Scan for inappropriate content
- **Moderator Logs** - View action history
- **Appeal Manager** - Handle user appeals

**Status:** "All tools are ready to use"

**Use case:** Access specialized moderation utilities

---

### 8. 🌐 Server Status
**What it does:** Monitor server health and performance

**Metrics Displayed:**
- **Server Health:** 95-100% (randomized)
- **Status:** Online (green)
- **Online Users:** 1,000-9,999 (randomized)
- **Queue Length:** Level count pending processing
- **Response Time:** Server latency in milliseconds

**Status Message:** "All systems operational"

**Use case:** Check server infrastructure status

---

## 🎨 Interface Design

### Visual Elements
- **Background:** Semi-transparent dark overlay (black, 70% opacity)
- **Main Panel:** 420x280 square sprite with rounded corners
- **Title:** "Moderator Control Panel" in gold font
- **Role Indicator:** Shows your current role with color coding:
  - 🟡 **Gold** - Moderator
  - 🔴 **Red** - Elder Moderator
  - 🟢 **Green** - Leaderboard Moderator
  - 🔵 **Cyan** - Developer

### Button Layout
```
┌─────────────────────────────────┐
│  Moderator Control Panel        │
│  [Your Role]                    │
├─────────────────────────────────┤
│  [Reported]    [User Search]    │
│   Levels                        │
│                                 │
│  [Level]       [Mod Stats]      │
│   Queue                         │
│                                 │
│  [Ban/Unban]   [View Reports]   │
│   User                          │
│                                 │
│  [Mod Tools]   [Server Status]  │
│                                 │
└─────────────────────────────────┘
```

### Animations
- **Entrance:** Elastic scale-in effect (0.1 → 1.0 over 0.5s)
- **Exit:** Elastic scale-out effect (1.0 → 0.1 over 0.3s)
- **Buttons:** 1.2x size multiplier for hover feedback

---

## 🎯 Use Case Scenarios

### Scenario 1: Reviewing Reported Content
1. Open Control Panel
2. Click "Reported Levels"
3. Browse through unrated levels
4. Rate/delete inappropriate content
5. Return to menu

### Scenario 2: User Moderation
1. Open Control Panel
2. Click "User Search"
3. Enter username
4. Review user profile and reports
5. Use "Ban/Unban User" if needed

### Scenario 3: Daily Moderation Routine
1. Check "Server Status" for system health
2. Review "Mod Stats" to see your activity
3. Check "View Reports" for pending items
4. Process "Level Queue" for new submissions
5. Use "Mod Tools" as needed

### Scenario 4: Managing High-Priority Reports
1. Open "View Reports" to see statistics
2. Identify high-priority categories
3. Use "Reported Levels" and "User Search" to investigate
4. Take appropriate moderation actions
5. Document in "Moderator Logs" (via Mod Tools)

---

## 💡 Pro Tips

### Efficiency Tips
- **Keyboard Shortcuts:** Use ESC to close the panel quickly
- **Quick Access:** The button is always visible on the main menu
- **Batch Operations:** Use "Mass Level Action" for multiple levels
- **Report Priority:** Focus on high-priority items first

### Best Practices
- Check "Server Status" regularly to ensure system health
- Review "Mod Stats" to track your contributions
- Use "User Search" before taking ban actions
- Keep an eye on the notification badge for new reports

### Customization
- Toggle panel features in mod settings
- Adjust notification preferences
- Configure which buttons to display
- Set default views for each feature

---

## ⚠️ Important Notes

### Client-Side Simulation
All features are **simulated client-side** and do not affect actual game servers:
- Levels are not actually deleted
- Users are not actually banned
- Reports are randomly generated
- Statistics are simulated

### Purpose
This mod is designed for:
- **Entertainment** - Experience moderator features
- **Education** - Learn about moderation systems
- **Role-playing** - Simulate being a GD staff member

### Limitations
- Actions only affect your local game
- Other players cannot see your moderator status
- Statistics reset when mod is reloaded
- Report data is randomly generated each time

---

## 🔧 Troubleshooting

### Button Not Appearing
**Solution:** Ensure you have a moderator role (1-4) selected in settings

### Panel Not Opening
**Solution:** Check that the game is fully loaded and you're on the main menu

### Features Not Working
**Solution:** Verify mod is enabled in Geode mod manager

### Animation Lag
**Solution:** Reduce other mods or check system performance

---

## 📚 Related Documentation

- [Main README](README.md) - Overview and installation
- [Feature List](FEATURES.md) - Complete feature documentation
- [About](about.md) - Role descriptions and details
- [Changelog](changelog.md) - Version history

---

**Version:** 2.5.0  
**Last Updated:** February 12, 2026  
**Created by:** BitZ  
**Requires:** Geode 4.1.2+, GD 2.2074
