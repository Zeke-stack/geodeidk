/**
 * FakeGDMod - Professional Moderator & Developer Simulation  
 * Simplified build-compatible version
 * 
 * @author BitZ
 * @version 2.5.0
 */

#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <Geode/modify/ProfilePage.hpp>
#include <Geode/modify/LevelInfoLayer.hpp>

using namespace geode::prelude;

/**
 * Helper class for moderator utilities
 */
class ModHelper {
public:
    static bool hasModPrivileges() {
        int64_t modType = Mod::get()->getSettingValue<int64_t>("modType");
        return modType >= 1 && modType <= 4;
    }

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
};

/**
 * ProfilePage - Apply moderator badge
 */
class $modify(ProfilePage) {
    void loadPageFromUserInfo(GJUserScore* userScore) {
        if (this->m_ownProfile && ModHelper::hasModPrivileges()) {
            int64_t modType = Mod::get()->getSettingValue<int64_t>("modType");
            userScore->m_modBadge = (modType == 4) ? 2 : modType;
        }
        ProfilePage::loadPageFromUserInfo(userScore);
    }
};

/**
 * LevelInfoLayer - Add moderator features
 */
class $modify(LevelInfoLayer) {
    bool init(GJGameLevel* level, bool challenge) {
        if (!LevelInfoLayer::init(level, challenge)) return false;

        // Show level password if enabled
        if (Mod::get()->getSettingValue<bool>("showLevelPasswords") && 
            level->m_password > 0 && ModHelper::hasModPrivileges()) {
            
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
};

/**
 * MenuLayer - Add moderator menu button
 */
class $modify(MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) return false;

        if (!ModHelper::hasModPrivileges()) {
            return true;
        }

        // Create moderator button
        auto modBtnSprite = CCSprite::createWithSpriteFrameName("modBadge_01_001.png");
        if (modBtnSprite) {
            modBtnSprite->setScale(1.0f);
            
            auto modBtn = CCMenuItemSpriteExtra::create(
                modBtnSprite,
                this,
                menu_selector(MenuLayer::onModMenu)
            );

            auto menu = this->getChildByType<CCMenu>(0);
            if (menu) {
                modBtn->setPosition({CCDirector::sharedDirector()->getWinSize().width / 2 + 180, 30});
                menu->addChild(modBtn);
            }
        }

        // Welcome notification
        Notification::create(
            fmt::format("Welcome, {}!", ModHelper::getRoleName()),
            NotificationIcon::Info
        )->show();

        return true;
    }

    void onModMenu(CCObject*) {
        // Show moderator menu
        FLAlertLayer::create(
            "Moderator Control Panel",
            fmt::format(
                "<cy>Role:</c> {}\n\n"
                "<cg>Features Available:</c>\n"
                "- Level Management\n"
                "- User Moderation\n"
                "- Report System\n"
                "- Mod Tools\n\n"
                "Use level info screens and\n"
                "profile pages to access\n"
                "moderator features!",
                ModHelper::getRoleName()
            ),
            "OK"
        )->show();
    }
};
