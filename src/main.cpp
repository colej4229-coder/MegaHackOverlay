#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/Bindings.hpp>
#include <Geode/ui/SettingsPopup.hpp>
#include <Geode/utils/cocos.hpp>

using namespace geode::prelude;

class OverlayLayer : public cocos2d::CCLayer {
public:
    cocos2d::DrawNode* drawNode;

    bool init() override {
        if (!CCLayer::init()) return false;
        drawNode = cocos2d::DrawNode::create();
        this->addChild(drawNode, 1000);

        this->schedule([this](float) {
            drawNode->clear();
            auto size = CCDirector::sharedDirector()->getWinSize();
            cocos2d::Vec2 c(size.width/2, size.height/2);
            drawNode->drawLine({c.x-20, c.y}, {c.x+20, c.y});
            drawNode->drawLine({c.x, c.y-20}, {c.x, c.y+20});
        }, "overlayUpdate");
        return true;
    }
    CREATE_FUNC(OverlayLayer);
};

class $modify(PlayLayer) {
    void onEnter() {
        PlayLayer::onEnter();
        auto overlay = OverlayLayer::create();
        this->addChild(overlay, 1000);
    }
};

class $modify(MenuLayer) {
    void init() {
        MenuLayer::init();
        auto btn = CCMenuItemSpriteExtra::create(
            CCLabelBMFont::create("Overlay", "bigFont.fnt"),
            this, menu_selector(MenuLayer::onOverlaySettings)
        );
        btn->setPosition({-300, -200});
        this->m_pMenu->addChild(btn);
    }

    void onOverlaySettings(CCObject*) {
        auto popup = SettingsPopup::create("MegaHack Overlay", "Toggle overlay");
        popup->addToggle("Enable overlay", "enable_overlay");
        popup->show();
    }
};
