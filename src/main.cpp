#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>
#include <U8g2_for_Adafruit_GFX.h>

// ===== 已验证引脚 =====
#define TFT_SCLK 33
#define TFT_MOSI 14
#define TFT_RST  12
#define TFT_DC   13
#define TFT_CS   15

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);
U8G2_FOR_ADAFRUIT_GFX u8g2;

// ===== 64 卦名 =====
const char* hexagramNames[64] = {
  "乾为天", "坤为地", "水雷屯", "山水蒙", "水天需", "天水讼", "地水师", "水地比",
  "风天小畜", "天泽履", "地天泰", "天地否", "天火同人", "火天大有", "地山谦", "雷地豫",
  "泽雷随", "山风蛊", "地泽临", "风地观", "火雷噬嗑", "山火贲", "山地剥", "地雷复",
  "天雷无妄", "山天大畜", "山雷颐", "泽风大过", "坎为水", "离为火", "泽山咸", "雷风恒",
  "天山遁", "雷天大壮", "火地晋", "地火明夷", "风火家人", "火泽睽", "水山蹇", "雷水解",
  "山泽损", "风雷益", "泽天夬", "天风姤", "泽地萃", "地风升", "泽水困", "水风井",
  "泽火革", "火风鼎", "震为雷", "艮为山", "风山渐", "雷泽归妹", "雷火丰", "火山旅",
  "巽为风", "兑为泽", "风水涣", "水泽节", "风泽中孚", "雷山小过", "水火既济", "火水未济"
};

// ===== 64 卦辞（通行本原文）=====
const char* hexagramTexts[64] = {
  "元亨利贞。",
  "元亨，利牝马之贞。君子有攸往，先迷后得主，利。西南得朋，东北丧朋。安贞吉。",
  "元亨利贞，勿用有攸往，利建侯。",
  "亨。匪我求童蒙，童蒙求我。初筮告，再三渎，渎则不告。利贞。",
  "有孚，光亨，贞吉。利涉大川。",
  "有孚，窒惕，中吉，终凶。利见大人，不利涉大川。",
  "贞，丈人吉，无咎。",
  "吉。原筮，元永贞，无咎。不宁方来，后夫凶。",
  "亨。密云不雨，自我西郊。",
  "履虎尾，不咥人，亨。",
  "小往大来，吉亨。",
  "否之匪人，不利君子贞，大往小来。",
  "同人于野，亨。利涉大川，利君子贞。",
  "元亨。",
  "亨，君子有终。",
  "利建侯行师。",
  "元亨利贞，无咎。",
  "元亨，利涉大川。先甲三日，后甲三日。",
  "元亨利贞。至于八月有凶。",
  "盥而不荐，有孚颙若。",
  "亨。利用狱。",
  "亨。小利有攸往。",
  "不利有攸往。",
  "亨。出入无疾，朋来无咎。反复其道，七日来复。利有攸往。",
  "元亨利贞。其匪正有眚，不利有攸往。",
  "利贞。不家食吉，利涉大川。",
  "贞吉。观颐，自求口实。",
  "栋桡，利有攸往，亨。",
  "习坎，有孚，维心亨，行有尚。",
  "利贞，亨。畜牝牛吉。",
  "亨，利贞。取女吉。",
  "亨，无咎，利贞，利有攸往。",
  "亨，小利贞。",
  "利贞。",
  "康侯用锡马蕃庶，昼日三接。",
  "利艰贞。",
  "利女贞。",
  "小事吉。",
  "利西南，不利东北。利见大人，贞吉。",
  "利西南。无所往，其来复吉。有攸往，夙吉。",
  "有孚，元吉，无咎，可贞，利有攸往。曷之用？二簋可用享。",
  "利有攸往，利涉大川。",
  "扬于王庭，孚号有厉。告自邑，不利即戎，利有攸往。",
  "女壮，勿用取女。",
  "亨。王假有庙，利见大人，亨，利贞。用大牲吉，利有攸往。",
  "元亨，用见大人，勿恤，南征吉。",
  "亨，贞，大人吉，无咎。有言不信。",
  "改邑不改井，无丧无得，往来井井。汔至亦未繘井，羸其瓶，凶。",
  "己日乃孚，元亨利贞，悔亡。",
  "元吉，亨。",
  "亨。震来虩虩，笑言哑哑。震惊百里，不丧匕鬯。",
  "艮其背，不获其身；行其庭，不见其人。无咎。",
  "女归吉，利贞。",
  "征凶，无攸利。",
  "亨，王假之，勿忧，宜日中。",
  "小亨，旅贞吉。",
  "小亨，利有攸往，利见大人。",
  "亨，利贞。",
  "亨。王假有庙，利涉大川，利贞。",
  "亨。苦节不可贞。",
  "豚鱼吉，利涉大川，利贞。",
  "亨，利贞。可小事，不可大事。飞鸟遗之音，不宜上，宜下，大吉。",
  "亨，小利贞，初吉终乱。",
  "亨。小狐汔济，濡其尾，无攸利。"
};

// ===== 状态机 =====
enum DisplayState { STATE_IDLE, STATE_HEXAGRAM, STATE_TEXT };
DisplayState state = STATE_IDLE;
int currentIndex = 0;

// ===== 摇卦 =====
int tossYao() {
  int sum = 0;
  for (int i = 0; i < 3; i++) sum += (random(2) == 1) ? 3 : 2;
  return sum;
}

int trigramNum(int bits) {
  switch (bits) {
    case 0b111: return 1; // 乾
    case 0b011: return 2; // 兑
    case 0b101: return 3; // 离
    case 0b001: return 4; // 震
    case 0b110: return 5; // 巽
    case 0b010: return 6; // 坎
    case 0b100: return 7; // 艮
    default:    return 8; // 坤
  }
}

// 修正后的上下卦表（与上一轮一致）
const int hexLower[64] = {
  1, 8, 4, 6, 1, 6, 6, 8, 1, 2, 1, 8, 3, 1, 7, 8,
  4, 5, 2, 8, 4, 3, 8, 4, 4, 1, 4, 5, 6, 3, 7, 5,
  7, 1, 8, 3, 3, 2, 7, 6, 2, 4, 1, 5, 8, 5, 6, 5,
  3, 5, 4, 7, 7, 2, 3, 7, 5, 2, 6, 2, 2, 7, 3, 6
};
const int hexUpper[64] = {
  1, 8, 6, 7, 6, 1, 8, 6, 5, 1, 8, 1, 1, 3, 8, 4,
  2, 7, 8, 5, 3, 7, 7, 8, 1, 7, 7, 2, 6, 3, 2, 4,
  1, 4, 3, 8, 5, 3, 6, 4, 7, 5, 2, 1, 2, 8, 2, 6,
  2, 3, 4, 7, 5, 4, 4, 3, 5, 2, 5, 6, 5, 4, 6, 3
};

int computeHexagramIndex(int yao[]) {
  int binary = 0;
  for (int i = 0; i < 6; i++) {
    int yang = (yao[i] == 7 || yao[i] == 9) ? 1 : 0;
    binary |= (yang << i);
  }
  int lowerNum = trigramNum(binary & 0x07);
  int upperNum = trigramNum((binary >> 3) & 0x07);
  for (int i = 0; i < 64; i++) {
    if (hexLower[i] == lowerNum && hexUpper[i] == upperNum) return i;
  }
  return 0;
}

// ===== 绘制单爻 =====
void drawYao(int value, int yPos) {
  int centerX = 64, width = 80, height = 6;
  int left = centerX - width / 2, right = centerX + width / 2;
  if (value == 7 || value == 9) {
    tft.fillRect(left, yPos, width, height, ST77XX_WHITE);
  } else {
    tft.fillRect(left, yPos, width / 2 - 4, height, ST77XX_WHITE);
    tft.fillRect(centerX + 4, yPos, width / 2 - 4, height, ST77XX_WHITE);
  }
  if (value == 6 || value == 9) tft.fillCircle(right + 10, yPos + height / 2, 3, ST77XX_RED);
}

// ===== UTF-8 感知的自动换行打印 =====
// ===== UTF-8 感知的自动换行打印（精确测量宽度）=====
// ===== UTF-8 感知的自动换行打印（带宽度合理性检查）=====
// ===== UTF-8 感知的自动换行打印（固定宽度，不依赖库测量）=====
void printWrapped(const char* text, int x, int y, int maxWidth, int lineHeight) {
  int cx = x, cy = y;
  const char* p = text;
  while (*p) {
    if (*p == '\n') { cx = x; cy += lineHeight; p++; continue; }

    int len = 1;
    unsigned char c = (unsigned char)*p;
    if ((c & 0xE0) == 0xC0) len = 2;
    else if ((c & 0xF0) == 0xE0) len = 3;
    else if ((c & 0xF8) == 0xF0) len = 4;

    // 多字节（中文/全角标点）= 12px，单字节 ASCII = 6px
    int w = (len > 1) ? 12 : 6;

    if (cx + w > x + maxWidth) {
      cx = x;
      cy += lineHeight;
    }

    char buf[5] = {0};
    memcpy(buf, p, len);
    u8g2.setCursor(cx, cy);
    u8g2.print(buf);
    cx += w;
    p += len;
  }
}

// ===== 起始页 =====
void showIdleScreen() {
  tft.fillScreen(ST77XX_BLACK);
  u8g2.setForegroundColor(ST77XX_CYAN);
  u8g2.setFont(u8g2_font_wqy16_t_gb2312);
  u8g2.setCursor(10, 60);
  u8g2.print("起卦");

  u8g2.setForegroundColor(ST77XX_WHITE);
  u8g2.setFont(u8g2_font_wqy12_t_gb2312);
  u8g2.setCursor(10, 90);
  u8g2.print("按 BOOT 开始摇卦");
}

// ===== 起卦并显示卦象，返回卦序 =====
int castHexagram() {
  int yao[6];
  for (int i = 0; i < 6; i++) { yao[i] = tossYao(); delay(400); }
  int index = computeHexagramIndex(yao);

  tft.fillScreen(ST77XX_BLACK);

  u8g2.setForegroundColor(ST77XX_YELLOW);
  u8g2.setFont(u8g2_font_wqy12_t_gb2312);
  u8g2.setCursor(2, 14);
  u8g2.print("");//起卦结果

  u8g2.setForegroundColor(ST77XX_GREEN);
  u8g2.setFont(u8g2_font_wqy16_t_gb2312);
  u8g2.setCursor(50, 16);
  u8g2.print(hexagramNames[index]);

  for (int i = 5; i >= 0; i--) {
    drawYao(yao[i], 30 + (5 - i) * 18);
  }
  return index;
}

// ===== 显示卦辞 =====
void showHexagramText(int index) {
  tft.fillScreen(ST77XX_BLACK);

  // 物理屏幕是 128×128，驱动却按 160 宽计算，这里强制用 128
  const int screenW = 128;

  u8g2.setForegroundColor(ST77XX_YELLOW);
  u8g2.setFont(u8g2_font_wqy12_t_gb2312);
  u8g2.setCursor(2, 14);
  u8g2.print(hexagramNames[index]);

  // “卦辞”两个汉字 = 24px，右对齐
  u8g2.setCursor(screenW - 24 - 4, 14);
  u8g2.print("卦辞");

  u8g2.setForegroundColor(ST77XX_WHITE);
  printWrapped(hexagramTexts[index], 4, 34, screenW - 8, 15);
}

void setup() {
  Serial.begin(115200);
  delay(200);
  tft.initR(INITR_GREENTAB);//INITR_144GREENTAB
  tft.setRotation(1);
  tft.fillScreen(ST77XX_BLACK);

  u8g2.begin(tft);
  u8g2.setBackgroundColor(ST77XX_BLACK);
  randomSeed(esp_random());

  showIdleScreen();
}

void loop() {
  if (digitalRead(0) == LOW) {
    delay(30);
    if (digitalRead(0) == LOW) {
      switch (state) {
        case STATE_IDLE:
          currentIndex = castHexagram();
          state = STATE_HEXAGRAM;
          break;
        case STATE_HEXAGRAM:
          showHexagramText(currentIndex);
          state = STATE_TEXT;
          break;
        case STATE_TEXT:
          showIdleScreen();
          state = STATE_IDLE;
          break;
      }
      while (digitalRead(0) == LOW) delay(10); // 等待松开
    }
  }
}