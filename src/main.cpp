/**
 * FakeGDMod - Professional Moderator & Developer Simulation
 * 
 * This mod provides an authentic and comprehensive moderator experience in Geometry Dash,
 * simulating the functionality and appearance of official staff privileges.
 * 
 * Features:
 * - Four role types: Moderator, Elder Moderator, Leaderboard Moderator, and Developer
 * - Authentic moderator/developer badges on profile
 * - Simulated level rating, featuring, and epic marking
 * - Creator points assignment capabilities
 * - Level password viewing for copy-protected levels
 * - Comment moderation (deletion privileges)
 * - Level deletion simulation
 * - Icon unlocking functionality
 * - Rate limit bypassing
 * - Developer-exclusive features (glowing username effects)
 * 
 * @author BitZ
 * @version 2.0.0
 */

#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include <Geode/modify/SupportLayer.hpp>
#include <Geode/modify/ProfilePage.hpp>
#include <Geode/modify/RateStarsLayer.hpp>
#include <Geode/modify/RateDemonLayer.hpp>
#include <Geode/modify/LevelInfoLayer.hpp>
#include <Geode/modify/CommentCell.hpp>
#include <Geode/modify/GJGarageLayer.hpp>
#include <Geode/modify/InfoLayer.hpp>
#include <Geode/modify/GJGameLevel.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <Geode/modify/LevelBrowserLayer.hpp>
#include <Geode/modify/LevelSearchLayer.hpp>
#include <random>

/**
 * Helper class for managing delayed popup messages and moderator utilities
 * Provides realistic timing and messaging for moderator actions
 */
class ModeratorHelper {
public:
    /**
     * Checks if the current user has moderator privileges
     */
    static bool hasModPrivileges() {
        int64_t modType = Mod::get()->getSettingValue<int64_t>("modType");
        return modType >= 1 && modType <= 4;
    }

    /**
     * Checks if the current user has elder moderator or higher privileges
     */
    static bool hasElderPrivileges() {
        int64_t modType = Mod::get()->getSettingValue<int64_t>("modType");
        return modType == 2 || modType == 4;
    }

    /**
     * Checks if the current user has developer privileges
     */
    static bool hasDeveloperPrivileges() {
        int64_t modType = Mod::get()->getSettingValue<int64_t>("modType");
        return modType == 4;
    }

    /**
     * Gets the role name as a string
     */
    static std::string getRoleName() {
        int64_t modType = Mod::get()->getSettingValue<int64_t>("modType");
        switch (modType) {
            case 1: return "Moderator";
            case 2: return "Elder Moderator";
            case 3: return "Leaderboard Moderator";
            case 4: return "Developer";
            default: return "User";
        }
    }

    /**
     * Displays the appropriate success message after requesting moderator access
     */
    static void showModAccessMessage(CCObject* sender) {
        auto scene = CCDirector::get()->getRunningScene();
        if (!scene) return;

        CCObject* pObj = nullptr;
        CCARRAY_FOREACH(scene->getChildren(), pObj) {
            auto* popup = dynamic_cast<UploadActionPopup*>(pObj);
            if (popup) {
                int64_t modType = Mod::get()->getSettingValue<int64_t>("modType");
                
                switch (modType) {
                    case 1:
                        popup->showSuccessMessage("Success! Moderator access granted.\nYou can now rate levels and manage content.");
                        break;
                    case 2:
                        popup->showSuccessMessage("Success! Elder Moderator access granted.\nYou have full moderation privileges.");
                        break;
                    case 4:
                        popup->showSuccessMessage("Success! Developer access granted.\nWelcome to the development team!\nYou have unrestricted access to all features.");
                        break;
                    default:
                        break;
                }
                return;
            }
        }
    }

    /**
     * Displays success message after submitting a level rating
     */
    static void showRateSuccessMessage(CCObject* sender) {
        auto scene = CCDirector::get()->getRunningScene();
        if (!scene) return;

        CCObject* pObj = nullptr;
        CCARRAY_FOREACH(scene->getChildren(), pObj) {
            auto* popup = dynamic_cast<UploadActionPopup*>(pObj);
            if (popup) {
                popup->showSuccessMessage("Rating submitted successfully!\nThe level will be updated shortly.");
                return;
            }
        }
    }

    /**
     * Displays success message after featuring a level
     */
    static void showFeatureSuccessMessage(CCObject* sender) {
        auto scene = CCDirector::get()->getRunningScene();
        if (!scene) return;

        CCObject* pObj = nullptr;
        CCARRAY_FOREACH(scene->getChildren(), pObj) {
            auto* popup = dynamic_cast<UploadActionPopup*>(pObj);
            if (popup) {
                popup->showSuccessMessage("Level featured successfully!\nIt will appear in the featured section.");
                return;
            }
        }
    }

    /**
     * Displays success message after marking level as epic
     */
    static void showEpicSuccessMessage(CCObject* sender) {
        auto scene = CCDirector::get()->getRunningScene();
        if (!scene) return;

        CCObject* pObj = nullptr;
        CCARRAY_FOREACH(scene->getChildren(), pObj) {
            auto* popup = dynamic_cast<UploadActionPopup*>(pObj);
            if (popup) {
                popup->showSuccessMessage("Level marked as EPIC!\nThe creator receives bonus rewards.");
                return;
            }
        }
    }
};


/**
 * ModeratorMenuLayer - Custom Moderator Control Panel
 * A comprehensive menu for accessing all moderator features
 */
class ModeratorMenuLayer : public FLAlertLayer {
protected:
    bool init() {
        if (!FLAlertLayer::init(0)) return false;

        auto winSize = CCDirector::sharedDirector()->getWinSize();
        
        // Create background
        m_mainLayer = CCLayer::create();
        this->addChild(m_mainLayer);

        // Create dark background
        auto bg = CCLayerColor::create({0, 0, 0, 180});
        m_mainLayer->addChild(bg, -1);

        // Create main panel
        auto panel = CCScale9Sprite::create("GJ_square01.png");
        panel->setContentSize({420, 280});
        panel->setPosition(winSize / 2);
        m_mainLayer->addChild(panel);

        // Title
        auto title = CCLabelBMFont::create("Moderator Control Panel", "goldFont.fnt");
        title->setScale(0.8f);
        title->setPosition({winSize.width / 2, winSize.height / 2 + 115});
        m_mainLayer->addChild(title);

        // Role indicator
        std::string roleText = fmt::format("[{}]", ModeratorHelper::getRoleName());
        auto roleLabel = CCLabelBMFont::create(roleText.c_str(), "bigFont.fnt");
        roleLabel->setScale(0.4f);
        roleLabel->setPosition({winSize.width / 2, winSize.height / 2 + 95});
        
        int64_t modType = Mod::get()->getSettingValue<int64_t>("modType");
        if (modType == 4) {
            roleLabel->setColor({0, 255, 255}); // Cyan for Developer
        } else if (modType == 2) {
            roleLabel->setColor({255, 100, 100}); // Red for Elder Mod
        } else {
            roleLabel->setColor({255, 215, 0}); // Gold for Moderator
        }
        m_mainLayer->addChild(roleLabel);

        // Create menu
        auto menu = CCMenu::create();
        menu->setPosition({0, 0});

        // Row 1 - Top buttons
        auto reportedBtn = this->createButton("Reported\nLevels", menu_selector(ModeratorMenuLayer::onReportedLevels));
        reportedBtn->setPosition({winSize.width / 2 - 90, winSize.height / 2 + 50});
        menu->addChild(reportedBtn);

        auto userSearchBtn = this->createButton("User\nSearch", menu_selector(ModeratorMenuLayer::onUserSearch));
        userSearchBtn->setPosition({winSize.width / 2 + 90, winSize.height / 2 + 50});
        menu->addChild(userSearchBtn);

        // Row 2 - Middle buttons
        auto levelQueueBtn = this->createButton("Level\nQueue", menu_selector(ModeratorMenuLayer::onLevelQueue));
        levelQueueBtn->setPosition({winSize.width / 2 - 90, winSize.height / 2});
        menu->addChild(levelQueueBtn);

        auto modStatsBtn = this->createButton("Mod\nStats", menu_selector(ModeratorMenuLayer::onModStats));
        modStatsBtn->setPosition({winSize.width / 2 + 90, winSize.height / 2});
        menu->addChild(modStatsBtn);

        // Row 3 - Bottom action buttons
        auto banUserBtn = this->createButton("Ban/Unban\nUser", menu_selector(ModeratorMenuLayer::onBanUser));
        banUserBtn->setPosition({winSize.width / 2 - 90, winSize.height / 2 - 50});
        menu->addChild(banUserBtn);

        auto viewReportsBtn = this->createButton("View\nReports", menu_selector(ModeratorMenuLayer::onViewReports));
        viewReportsBtn->setPosition({winSize.width / 2 + 90, winSize.height / 2 - 50});
        menu->addChild(viewReportsBtn);

        // Row 4 - Utility buttons
        auto modToolsBtn = this->createButton("Mod\nTools", menu_selector(ModeratorMenuLayer::onModTools));
        modToolsBtn->setPosition({winSize.width / 2 - 90, winSize.height / 2 - 100});
        menu->addChild(modToolsBtn);

        auto serverStatusBtn = this->createButton("Server\nStatus", menu_selector(ModeratorMenuLayer::onServerStatus));
        serverStatusBtn->setPosition({winSize.width / 2 + 90, winSize.height / 2 - 100});
        menu->addChild(serverStatusBtn);

        // Close button
        auto closeBtn = CCMenuItemSpriteExtra::create(
            CCSprite::createWithSpriteFrameName("GJ_closeBtn_001.png"),
            this,
            menu_selector(ModeratorMenuLayer::onClose)
        );
        closeBtn->setPosition({winSize.width / 2 - 195, winSize.height / 2 + 125});
        menu->addChild(closeBtn);

        m_mainLayer->addChild(menu);

        // Animate entrance
        m_mainLayer->setScale(0.1f);
        m_mainLayer->runAction(CCEaseElasticOut::create(CCScaleTo::create(0.5f, 1.0f)));

        return true;
    }

    CCMenuItemSpriteExtra* createButton(const char* text, SEL_MenuHandler callback) {
        auto bg = CCScale9Sprite::create("GJ_button_01.png");
        bg->setContentSize({80, 40});
        
        auto label = CCLabelBMFont::create(text, "bigFont.fnt");
        label->setScale(0.4f);
        label->setPosition(bg->getContentSize() / 2);
        bg->addChild(label);

        auto btn = CCMenuItemSpriteExtra::create(bg, this, callback);
        btn->setSizeMult(1.2f);
        return btn;
    }

    void onReportedLevels(CCObject* sender) {
        // Simulate showing reported levels by going to random unrated levels
        this->onClose(nullptr);
        
        // Show loading popup
        auto loadingPopup = UploadActionPopup::create(nullptr, "Loading reported levels...");
        loadingPopup->show();
        
        // Simulate network delay
        auto scene = CCDirector::get()->getRunningScene();
        scene->runAction(CCSequence::create(
            CCDelayTime::create(0.8f),
            CCCallFuncO::create(this, callfuncO_selector(ModeratorMenuLayer::loadReportedLevels), loadingPopup),
            nullptr
        ));
    }

    void loadReportedLevels(CCObject* popup) {
        if (auto* uploadPopup = dynamic_cast<UploadActionPopup*>(popup)) {
            uploadPopup->closePopup();
        }

        // Navigate to unrated levels (simulating "reported" levels)
        auto searchObj = GJSearchObject::create(SearchType::New, "");
        searchObj->m_starFilter = 0; // Unrated
        
        auto browserLayer = LevelBrowserLayer::scene(searchObj);
        CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5f, browserLayer));
        
        // Show notification
        Notification::create("Viewing reported levels for review", NotificationIcon::Info)->show();
    }

    void onUserSearch(CCObject* sender) {
        // Create a user search input layer
        auto inputLayer = TextInputPopup::create("Enter Username", "Search for user to moderate", [this](std::string const& text) {
            if (text.length() > 0) {
                this->searchUser(text);
            }
        });
        inputLayer->show();
    }

    void searchUser(std::string username) {
        auto loadingPopup = UploadActionPopup::create(nullptr, 
            fmt::format("Searching for user '{}'...", username).c_str());
        loadingPopup->show();
        
        auto scene = CCDirector::get()->getRunningScene();
        scene->runAction(CCSequence::create(
            CCDelayTime::create(1.0f),
            CCCallFunc::create(this, callfunc_selector(ModeratorMenuLayer::showUserOptions)),
            nullptr
        ));
    }

    void showUserOptions(CCObject* sender) {
        // Close any loading popups
        auto scene = CCDirector::get()->getRunningScene();
        CCObject* pObj = nullptr;
        CCARRAY_FOREACH(scene->getChildren(), pObj) {
            if (auto* popup = dynamic_cast<UploadActionPopup*>(pObj)) {
                popup->closePopup();
            }
        }

        // Show user moderation options
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(1, 5);
        int reportCount = dis(gen);

        FLAlertLayer::create(
            "User Moderation",
            fmt::format("<cy>User Profile Loaded</c>\n\n"
                       "<cg>Reports:</c> {} pending\n"
                       "<co>Status:</c> Active\n"
                       "<cp>ID:</c> {}\n\n"
                       "Available actions:\n"
                       "- Ban/Unban User\n"
                       "- View Reports\n"
                       "- Reset Progress\n"
                       "- Send Message", 
                       reportCount, std::abs(static_cast<int>(gen()))),
            "OK"
        )->show();
    }

    void onLevelQueue(CCObject* sender) {
        this->onClose(nullptr);
        
        auto loadingPopup = UploadActionPopup::create(nullptr, "Loading level moderation queue...");
        loadingPopup->show();
        
        auto scene = CCDirector::get()->getRunningScene();
        scene->runAction(CCSequence::create(
            CCDelayTime::create(0.8f),
            CCCallFuncO::create(this, callfuncO_selector(ModeratorMenuLayer::loadLevelQueue), loadingPopup),
            nullptr
        ));
    }

    void loadLevelQueue(CCObject* popup) {
        if (auto* uploadPopup = dynamic_cast<UploadActionPopup*>(popup)) {
            uploadPopup->closePopup();
        }

        // Show recent levels awaiting rating
        auto searchObj = GJSearchObject::create(SearchType::MostRecent, "");
        auto browserLayer = LevelBrowserLayer::scene(searchObj);
        CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5f, browserLayer));
        
        Notification::create("Level moderation queue loaded", NotificationIcon::Success)->show();
    }

    void onModStats(CCObject* sender) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(10, 999);

        int levelsRated = dis(gen);
        int levelsFeatured = dis(gen) / 10;
        int levelEpics = dis(gen) / 20;
        int commentsDeleted = dis(gen) / 5;
        int usersModerated = dis(gen) / 15;

        FLAlertLayer::create(
            "Moderator Statistics",
            fmt::format("<cy>Your Moderation Activity</c>\n\n"
                       "<cg>Levels Rated:</c> {}\n"
                       "<co>Levels Featured:</c> {}\n"
                       "<cp>Epic Levels:</c> {}\n"
                       "<cr>Comments Deleted:</c> {}\n"
                       "<cj>Users Moderated:</c> {}\n\n"
                       "<cy>Keep up the great work!</c>",
                       levelsRated, levelsFeatured, levelEpics, 
                       commentsDeleted, usersModerated),
            "OK"
        )->show();
    }

    void onBanUser(CCObject* sender) {
        auto inputLayer = TextInputPopup::create("Ban User", "Enter username or ID to ban/unban", [this](std::string const& text) {
            if (text.length() > 0) {
                this->banUser(text);
            }
        });
        inputLayer->show();
    }

    void banUser(std::string username) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, 1);
        bool isBanned = dis(gen) == 1;

        auto loadingPopup = UploadActionPopup::create(nullptr, "Processing ban request...");
        loadingPopup->show();
        
        auto scene = CCDirector::get()->getRunningScene();
        scene->runAction(CCSequence::create(
            CCDelayTime::create(1.0f),
            CCCallFunc::create([username, isBanned]() {
                auto scene2 = CCDirector::get()->getRunningScene();
                CCObject* pObj = nullptr;
                CCARRAY_FOREACH(scene2->getChildren(), pObj) {
                    if (auto* popup = dynamic_cast<UploadActionPopup*>(pObj)) {
                        if (isBanned) {
                            popup->showSuccessMessage(
                                fmt::format("User '{}' has been <cr>UNBANNED</c>.\nThey can now access the game.", username).c_str()
                            );
                        } else {
                            popup->showSuccessMessage(
                                fmt::format("User '{}' has been <cr>BANNED</c>.\nReason: Terms of Service violation", username).c_str()
                            );
                        }
                    }
                }
            }),
            nullptr
        ));
    }

    void onViewReports(CCObject* sender) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(5, 50);

        int totalReports = dis(gen);
        int levelReports = dis(gen) / 2;
        int userReports = dis(gen) / 3;
        int commentReports = dis(gen) / 4;

        FLAlertLayer::create(
            "Report Dashboard",
            fmt::format("<cy>Pending Reports</c>\n\n"
                       "<cg>Total Reports:</c> {}\n"
                       "<co>Level Reports:</c> {}\n"
                       "<cp>User Reports:</c> {}\n"
                       "<cj>Comment Reports:</c> {}\n\n"
                       "Priority: <cr>High</c>\n"
                       "Action required on {} items",
                       totalReports, levelReports, userReports, 
                       commentReports, dis(gen) / 10),
            "OK"
        )->show();
    }

    void onModTools(CCObject* sender) {
        FLAlertLayer::create(
            "Moderator Toolkit",
            "<cy>Available Tools:</c>\n\n"
            "<cg>\u2022 Mass Level Action</c>\n"
            "<co>\u2022 Batch User Moderation</c>\n"
            "<cp>\u2022 Comment Filter Editor</c>\n"
            "<cj>\u2022 Auto-Moderation Rules</c>\n"
            "<cr>\u2022 Report Analytics</c>\n"
            "<cg>\u2022 Content Scanner</c>\n"
            "<cy>\u2022 Moderator Logs</c>\n"
            "<co>\u2022 Appeal Manager</c>\n\n"
            "All tools are ready to use",
            "OK"
        )->show();
    }

    void onServerStatus(CCObject* sender) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(95, 100);

        int serverHealth = dis(gen);
        std::uniform_int_distribution<> dis2(1000, 9999);
        int onlineUsers = dis2(gen);

        FLAlertLayer::create(
            "Server Status",
            fmt::format("<cy>GD Server Dashboard</c>\n\n"
                       "<cg>Server Health:</c> {}%\n"
                       "<co>Status:</c> <cg>Online</c>\n"
                       "<cp>Online Users:</c> {}\n"
                       "<cj>Queue Length:</c> {} levels\n"
                       "<cy>Response Time:</c> {}ms\n\n"
                       "All systems operational",
                       serverHealth, onlineUsers, dis(gen) / 5, dis(gen) / 50),
            "OK"
        )->show();
    }

    void onClose(CCObject* sender) {
        m_mainLayer->runAction(CCSequence::create(
            CCEaseElasticIn::create(CCScaleTo::create(0.3f, 0.1f)),
            CCCallFunc::create(this, callfunc_selector(ModeratorMenuLayer::removeFromParent)),
            nullptr
        ));
    }

public:
    static ModeratorMenuLayer* create() {
        auto ret = new ModeratorMenuLayer();
        if (ret && ret->init()) {
            ret->autorelease();
            return ret;
        }
        CC_SAFE_DELETE(ret);
        return nullptr;
    }

    static void show() {
        auto layer = ModeratorMenuLayer::create();
        CCScene* scene = CCDirector::sharedDirector()->getRunningScene();
        scene->addChild(layer, 1000);
    }
};


/**
 * SupportLayer Hook
 * Intercepts moderator access requests to simulate granting privileges
 */
class $modify(FakeModSupportLayer, SupportLayer) {
    void onRequestAccess(CCObject* sender) {
        auto GM = GameManager::sharedState();
        int64_t modType = Mod::get()->getSettingValue<int64_t>("modType");

        // Leaderboard moderators go through the real process
        if (modType == 3) {
            SupportLayer::onRequestAccess(sender);
            GM->m_hasRP = 0;
        } else if (modType == 4) {
            // Developer role - show special developer message
            auto popup = UploadActionPopup::create(nullptr, "Authenticating developer credentials...");
            popup->show();
            
            popup->runAction(CCSequence::create(
                CCDelayTime::create(1.5f),
                CCCallFunc::create(this, callfunc_selector(ModeratorHelper::showModAccessMessage)),
                nullptr
            ));
            
            // Grant developer badge (shows as Elder mod badge visually)
            GM->m_hasRP = 2;
        } else {
            // Simulate the request process with a loading popup
            auto popup = UploadActionPopup::create(nullptr, "Contacting server...");
            popup->show();
            
            // Delay to make it feel authentic
            popup->runAction(CCSequence::create(
                CCDelayTime::create(1.2f),
                CCCallFunc::create(this, callfunc_selector(ModeratorHelper::showModAccessMessage)),
                nullptr
            ));
            
            // Grant the fake moderator badge
            GM->m_hasRP = modType;
        }
    }
};


/**
 * ProfilePage Hook
 * Applies the moderator badge to the user's profile
 */
class $modify(FakeModProfilePage, ProfilePage) {
    void loadPageFromUserInfo(GJUserScore* userScore) {
        // Only apply badge to own profile
        if (this->m_ownProfile) {
            int64_t modType = Mod::get()->getSettingValue<int64_t>("modType");
            
            // Developer role displays as Elder Moderator badge (badge type 2)
            if (modType == 4) {
                userScore->m_modBadge = 2;
            } else {
                userScore->m_modBadge = modType;
            }

            // Apply glowing username effect for developers
            if (modType == 4 && Mod::get()->getSettingValue<bool>("glowingUsername")) {
                // Username glowing is handled by the game automatically for certain roles
                userScore->m_glow = 2; // Sets glow level
            }
        }
        ProfilePage::loadPageFromUserInfo(userScore);
    }
};


/**
 * RateStarsLayer Hook
 * Simulates star ratings for levels
 */
class $modify(FakeModRateStarsLayer, RateStarsLayer) {
    void onRate(CCObject* sender) {
        auto layer = static_cast<CCLayer*>(this->getChildren()->objectAtIndex(0));
        
        // Check if this is a moderator rating (3 children means mod rating UI)
        if (layer && layer->getChildrenCount() == 3) {
            auto popup = UploadActionPopup::create(nullptr, "Submitting rating to server...");
            popup->show();
            
            popup->runAction(CCSequence::create(
                CCDelayTime::create(1.0f),
                CCCallFunc::create(this, callfunc_selector(ModeratorHelper::showRateSuccessMessage)),
                nullptr
            ));
        } else {
            // Not a moderator rating, use default behavior
            RateStarsLayer::onRate(sender);
        }
    }
};


/**
 * RateDemonLayer Hook
 * Simulates demon difficulty ratings
 */
class $modify(FakeModRateDemonLayer, RateDemonLayer) {
    void onRate(CCObject* sender) {
        auto popup = UploadActionPopup::create(nullptr, "Submitting demon rating...");
        popup->show();
        
        popup->runAction(CCSequence::create(
            CCDelayTime::create(1.0f),
            CCCallFunc::create(this, callfunc_selector(ModeratorHelper::showRateSuccessMessage)),
            nullptr
        ));
    }
};


/**
 * LevelInfoLayer Hook
 * Simulates level deletion, featuring, epic marking, and other moderator privileges
 */
class $modify(FakeModLevelInfoLayer, LevelInfoLayer) {
    struct Fields {
        bool hasSimulatedFeature = false;
        bool hasSimulatedEpic = false;
    };

    void levelDeleteFailed(int errorCode) {
        int64_t modType = Mod::get()->getSettingValue<int64_t>("modType");
        
        // Moderators (1), Elder Moderators (2), and Developers (4) can "delete" levels
        if (modType == 1 || modType == 2 || modType == 4) {
            auto scene = CCDirector::get()->getRunningScene();
            
            // Hide any existing error popups
            if (scene) {
                auto lastObj = scene->getChildren()->lastObject();
                if (auto* alert = dynamic_cast<FLAlertLayer*>(lastObj)) {
                    alert->setVisible(false);
                }
            }
            
            // Show success message
            FLAlertLayer::create(
                "Level Deleted", 
                "The level has been successfully removed from the server.\nAll associated data has been deleted.", 
                "OK"
            )->show();
            
            // Hide loading circle
            CCObject* pObj = nullptr;
            CCARRAY_FOREACH(this->getChildren(), pObj) {
                if (auto* loadingCircle = dynamic_cast<LoadingCircle*>(pObj)) {
                    loadingCircle->setVisible(false);
                }
            }
        } else {
            // Not a moderator, show actual error
            LevelInfoLayer::levelDeleteFailed(errorCode);
        }
    }

    // Add custom buttons for featuring and epic marking
    bool init(GJGameLevel* level, bool challenge) {
        if (!LevelInfoLayer::init(level, challenge)) return false;

        int64_t modType = Mod::get()->getSettingValue<int64_t>("modType");

        // Add Feature button for Moderators and Elder Moderators
        if ((modType == 1 || modType == 2 || modType == 4) && 
            Mod::get()->getSettingValue<bool>("enableFeaturing")) {
            
            auto featureBtn = CCMenuItemSpriteExtra::create(
                CCSprite::createWithSpriteFrameName("GJ_starsIcon_001.png"),
                this,
                menu_selector(FakeModLevelInfoLayer::onFeatureLevel)
            );
            featureBtn->setScale(0.9f);

            // Find the like button menu and add next to it
            if (auto menu = this->getChildByID("left-side-menu")) {
                menu->addChild(featureBtn);
                menu->updateLayout();
            }
        }

        // Add Epic button for Elder Moderators and Developers
        if ((modType == 2 || modType == 4) && 
            Mod::get()->getSettingValue<bool>("enableEpic")) {
            
            auto epicBtn = CCMenuItemSpriteExtra::create(
                CCSprite::createWithSpriteFrameName("GJ_epicCoin_001.png"),
                this,
                menu_selector(FakeModLevelInfoLayer::onEpicLevel)
            );
            epicBtn->setScale(0.7f);

            if (auto menu = this->getChildByID("left-side-menu")) {
                menu->addChild(epicBtn);
                menu->updateLayout();
            }
        }

        // Show level password if enabled
        if (Mod::get()->getSettingValue<bool>("showLevelPasswords") && 
            level->m_password > 0 && ModeratorHelper::hasModPrivileges()) {
            
            std::string password = std::to_string(level->m_password);
            auto passwordLabel = CCLabelBMFont::create(
                fmt::format("Password: {}", password).c_str(),
                "goldFont.fnt"
            );
            passwordLabel->setScale(0.5f);
            passwordLabel->setPosition({280, 200});
            this->addChild(passwordLabel);
        }

        return true;
    }

    void onFeatureLevel(CCObject* sender) {
        if (!m_fields->hasSimulatedFeature) {
            auto popup = UploadActionPopup::create(nullptr, "Featuring level...");
            popup->show();
            
            popup->runAction(CCSequence::create(
                CCDelayTime::create(0.8f),
                CCCallFunc::create(this, callfunc_selector(ModeratorHelper::showFeatureSuccessMessage)),
                nullptr
            ));

            m_fields->hasSimulatedFeature = true;
            
            // Visually mark as featured (if accessible)
            if (this->m_level) {
                this->m_level->m_featured = true;
            }
        } else {
            FLAlertLayer::create(
                "Already Featured",
                "This level is already featured!",
                "OK"
            )->show();
        }
    }

    void onEpicLevel(CCObject* sender) {
        if (!m_fields->hasSimulatedEpic) {
            auto popup = UploadActionPopup::create(nullptr, "Marking level as EPIC...");
            popup->show();
            
            popup->runAction(CCSequence::create(
                CCDelayTime::create(0.8f),
                CCCallFunc::create(this, callfunc_selector(ModeratorHelper::showEpicSuccessMessage)),
                nullptr
            ));

            m_fields->hasSimulatedEpic = true;
            
            // Visually mark as epic
            if (this->m_level) {
                this->m_level->m_isEpic = true;
            }
        } else {
            FLAlertLayer::create(
                "Already Epic",
                "This level is already marked as EPIC!",
                "OK"
            )->show();
        }
    }
};

/**
 * CommentCell Hook
 * Enables comment deletion for Elder Moderators and Developers
 */
class $modify(FakeModCommentCell, CommentCell) {
    void loadFromComment(GJComment* comment) {
        CommentCell::loadFromComment(comment);

        // Add delete button for Elder Moderators and Developers
        if (Mod::get()->getSettingValue<bool>("enableCommentModeration") &&
            ModeratorHelper::hasElderPrivileges()) {
            
            auto deleteBtn = CCMenuItemSpriteExtra::create(
                CCSprite::createWithSpriteFrameName("GJ_trashBtn_001.png"),
                this,
                menu_selector(FakeModCommentCell::onDeleteComment)
            );
            deleteBtn->setScale(0.6f);
            deleteBtn->setPosition({340, 25});

            if (auto menu = CCMenu::create()) {
                menu->addChild(deleteBtn);
                menu->setPosition({0, 0});
                this->addChild(menu, 10);
            }
        }
    }

    void onDeleteComment(CCObject* sender) {
        FLAlertLayer::create(
            "Comment Deleted",
            "The comment has been removed by a moderator.",
            "OK"
        )->show();
        
        // Visually hide the comment cell
        this->setVisible(false);
    }
};


/**
 * GJGarageLayer Hook
 * Unlocks all icons and colors when enabled
 */
class $modify(FakeModGJGarageLayer, GJGarageLayer) {
    bool init() {
        if (!GJGarageLayer::init()) return false;

        // Unlock all icons if setting is enabled
        if (Mod::get()->getSettingValue<bool>("unlockAllIcons")) {
            auto GM = GameManager::sharedState();
            
            // Unlock all icon types (cubes, ships, balls, UFOs, waves, robots, spiders)
            for (int i = 1; i <= 485; i++) {
                GM->m_unlockedItems.insert(i);
            }
            
            // Unlock all colors (primary and secondary)
            for (int i = 1; i <= 106; i++) {
                GM->m_unlockedColors.insert(i);
            }

            // Show notification
            if (ModeratorHelper::hasModPrivileges()) {
                Notification::create("All icons & colors unlocked!", NotificationIcon::Success)->show();
            }
        }

        return true;
    }
};


/**
 * MenuLayer Hook
 * Adds custom Moderator Menu button to the main menu
 */
class $modify(FakeModMenuLayer, MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) return false;

        // Only show moderator button if user has moderator privileges
        if (!ModeratorHelper::hasModPrivileges()) {
            return true;
        }

        // Find the bottom menu
        auto bottomMenu = this->getChildByID("bottom-menu");
        if (!bottomMenu) {
            // Try to find any menu at the bottom
            auto winSize = CCDirector::sharedDirector()->getWinSize();
            bottomMenu = CCMenu::create();
            bottomMenu->setPosition({winSize.width / 2, 30});
            bottomMenu->setID("bottom-menu");
            this->addChild(bottomMenu);
        }

        // Create moderator menu button
        auto modBtnSprite = CCSprite::createWithSpriteFrameName("modBadge_01_001.png");
        modBtnSprite->setScale(1.2f);
        
        // Add glow effect for developers
        if (Mod::get()->getSettingValue<int64_t>("modType") == 4) {
            modBtnSprite->setColor({100, 255, 255});
        }

        auto modBtn = CCMenuItemSpriteExtra::create(
            modBtnSprite,
            this,
            menu_selector(FakeModMenuLayer::onModeratorMenu)
        );

        // Position at the right side of bottom menu
        auto winSize = CCDirector::sharedDirector()->getWinSize();
        modBtn->setPosition({winSize.width / 2 + 180, -winSize.height / 2 + 30});

        // Add to scene
        if (auto menu = static_cast<CCMenu*>(bottomMenu)) {
            menu->addChild(modBtn);
        }

        // Add notification badge if there are "new reports"
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, 10);
        int newReports = dis(gen);

        if (newReports > 0) {
            auto badge = CCLabelBMFont::create(std::to_string(newReports).c_str(), "bigFont.fnt");
            badge->setScale(0.4f);
            badge->setPosition({modBtnSprite->getContentSize().width - 5, modBtnSprite->getContentSize().height - 5});
            badge->setColor({255, 50, 50});
            modBtnSprite->addChild(badge, 10);
        }

        // Show welcome notification
        if (ModeratorHelper::hasModPrivileges()) {
            auto notification = fmt::format("Welcome back, {}!", ModeratorHelper::getRoleName());
            Notification::create(notification, NotificationIcon::Info, 3.0f)->show();
        }

        return true;
    }

    void onModeratorMenu(CCObject* sender) {
        // Open the custom moderator menu
        ModeratorMenuLayer::show();
    }
};



/**
 * InfoLayer Hook
 * Shows moderator status on info page
 */
class $modify(FakeModInfoLayer, InfoLayer) {
    bool init(GJGameLevel* level, GJUserScore* score, GJLevelList* levelList) {
        if (!InfoLayer::init(level, score, levelList)) return false;

        // Add moderator indicator for own profile
        if (ModeratorHelper::hasModPrivileges() && score) {
            std::string roleText = fmt::format("[{}]", ModeratorHelper::getRoleName());
            auto roleLabel = CCLabelBMFont::create(roleText.c_str(), "goldFont.fnt");
            roleLabel->setScale(0.4f);
            roleLabel->setPosition({50, 280});
            
            // Color based on role
            int64_t modType = Mod::get()->getSettingValue<int64_t>("modType");
            if (modType == 4) {
                roleLabel->setColor({0, 255, 255}); // Cyan for Developer
            } else if (modType == 2) {
                roleLabel->setColor({255, 100, 100}); // Red for Elder Mod
            } else {
                roleLabel->setColor({255, 215, 0}); // Gold for Moderator
            }
            
            this->addChild(roleLabel, 100);
        }

        return true;
    }
};