#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>
#include <U8g2_for_Adafruit_GFX.h>

#define TFT_SCLK 33
#define TFT_MOSI 14
#define TFT_RST  12
#define TFT_DC   13
#define TFT_CS   15

#define COLOR_DIM 0x8410  // 暗灰，RGB565

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);
U8G2_FOR_ADAFRUIT_GFX u8g2;

// ===== 64 卦名 =====
const char* hexagramNames[64] = {
  "乾为天","坤为地","水雷屯","山水蒙","水天需","天水讼","地水师","水地比",
  "风天小畜","天泽履","地天泰","天地否","天火同人","火天大有","地山谦","雷地豫",
  "泽雷随","山风蛊","地泽临","风地观","火雷噬嗑","山火贲","山地剥","地雷复",
  "天雷无妄","山天大畜","山雷颐","泽风大过","坎为水","离为火","泽山咸","雷风恒",
  "天山遁","雷天大壮","火地晋","地火明夷","风火家人","火泽睽","水山蹇","雷水解",
  "山泽损","风雷益","泽天夬","天风姤","泽地萃","地风升","泽水困","水风井",
  "泽火革","火风鼎","震为雷","艮为山","风山渐","雷泽归妹","雷火丰","火山旅",
  "巽为风","兑为泽","风水涣","水泽节","风泽中孚","雷山小过","水火既济","火水未济"
};

// ===== 64 卦辞 =====
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

// ===== 384 爻辞（64卦×6爻，通行本序）=====
const char* yaoTexts[64][6] = {
  // 0 乾
  {"初九：潜龙勿用。","九二：见龙在田，利见大人。","九三：君子终日乾乾，夕惕若厉，无咎。","九四：或跃在渊，无咎。","九五：飞龙在天，利见大人。","上九：亢龙有悔。"},
  // 1 坤
  {"初六：履霜，坚冰至。","六二：直方大，不习无不利。","六三：含章可贞。或从王事，无成有终。","六四：括囊，无咎无誉。","六五：黄裳，元吉。","上六：龙战于野，其血玄黄。"},
  // 2 屯
  {"初九：磐桓，利居贞，利建侯。","六二：屯如邅如，乘马班如。匪寇婚媾，女子贞不字，十年乃字。","六三：即鹿无虞，惟入于林中，君子几不如舍，往吝。","六四：乘马班如，求婚媾，往吉，无不利。","九五：屯其膏，小贞吉，大贞凶。","上六：乘马班如，泣血涟如。"},
  // 3 蒙
  {"初六：发蒙，利用刑人，用说桎梏，以往吝。","九二：包蒙吉，纳妇吉，子克家。","六三：勿用取女，见金夫，不有躬，无攸利。","六四：困蒙，吝。","六五：童蒙，吉。","上九：击蒙，不利为寇，利御寇。"},
  // 4 需
  {"初九：需于郊。利用恒，无咎。","九二：需于沙。小有言，终吉。","九三：需于泥，致寇至。","六四：需于血，出自穴。","九五：需于酒食，贞吉。","上六：入于穴，有不速之客三人来，敬之终吉。"},
  // 5 讼
  {"初六：不永所事，小有言，终吉。","九二：不克讼，归而逋，其邑人三百户，无眚。","六三：食旧德，贞厉，终吉。或从王事，无成。","九四：不克讼，复即命，渝安贞，吉。","九五：讼，元吉。","上九：或锡之鞶带，终朝三褫之。"},
  // 6 师
  {"初六：师出以律，否臧凶。","九二：在师中，吉无咎，王三锡命。","六三：师或舆尸，凶。","六四：师左次，无咎。","六五：田有禽，利执言，无咎。长子帅师，弟子舆尸，贞凶。","上六：大君有命，开国承家，小人勿用。"},
  // 7 比
  {"初六：有孚比之，无咎。有孚盈缶，终来有它，吉。","六二：比之自内，贞吉。","六三：比之匪人。","六四：外比之，贞吉。","九五：显比，王用三驱，失前禽。邑人不诫，吉。","上六：比之无首，凶。"},
  // 8 小畜
  {"初九：复自道，何其咎，吉。","九二：牵复，吉。","九三：舆说辐，夫妻反目。","六四：有孚，血去惕出，无咎。","九五：有孚挛如，富以其邻。","上九：既雨既处，尚德载，妇贞厉。月几望，君子征凶。"},
  // 9 履
  {"初九：素履，往无咎。","九二：履道坦坦，幽人贞吉。","六三：眇能视，跛能履，履虎尾，咥人，凶。武人为于大君。","九四：履虎尾，愬愬终吉。","九五：夬履，贞厉。","上九：视履考祥，其旋元吉。"},
  // 10 泰
  {"初九：拔茅茹，以其汇，征吉。","九二：包荒，用冯河，不遐遗，朋亡，得尚于中行。","九三：无平不陂，无往不复，艰贞无咎。勿恤其孚，于食有福。","六四：翩翩不富，以其邻，不戒以孚。","六五：帝乙归妹，以祉元吉。","上六：城复于隍，勿用师。自邑告命，贞吝。"},
  // 11 否
  {"初六：拔茅茹，以其汇，贞吉亨。","六二：包承。小人吉，大人否亨。","六三：包羞。","九四：有命无咎，畴离祉。","九五：休否，大人吉。其亡其亡，系于苞桑。","上九：倾否，先否后喜。"},
  // 12 同人
  {"初九：同人于门，无咎。","六二：同人于宗，吝。","九三：伏戎于莽，升其高陵，三岁不兴。","九四：乘其墉，弗克攻，吉。","九五：同人，先号啕而后笑。大师克相遇。","上九：同人于郊，无悔。"},
  // 13 大有
  {"初九：无交害，匪咎，艰则无咎。","九二：大车以载，有攸往，无咎。","九三：公用亨于天子，小人弗克。","九四：匪其彭，无咎。","六五：厥孚交如，威如，吉。","上九：自天佑之，吉无不利。"},
  // 14 谦
  {"初六：谦谦君子，用涉大川，吉。","六二：鸣谦，贞吉。","九三：劳谦，君子有终，吉。","六四：无不利，撝谦。","六五：不富，以其邻，利用侵伐，无不利。","上六：鸣谦，利用行师，征邑国。"},
  // 15 豫
  {"初六：鸣豫，凶。","六二：介于石，不终日，贞吉。","六三：盱豫，悔。迟有悔。","九四：由豫，大有得。勿疑。朋盍簪。","六五：贞疾，恒不死。","上六：冥豫，成有渝，无咎。"},
  // 16 随
  {"初九：官有渝，贞吉。出门交有功。","六二：系小子，失丈夫。","六三：系丈夫，失小子。随有求得，利居贞。","九四：随有获，贞凶。有孚在道，以明，何咎。","九五：孚于嘉，吉。","上六：拘系之，乃从维之。王用亨于西山。"},
  // 17 蛊
  {"初六：干父之蛊，有子，考无咎，厉终吉。","九二：干母之蛊，不可贞。","九三：干父之蛊，小有悔，无大咎。","六四：裕父之蛊，往见吝。","六五：干父之蛊，用誉。","上九：不事王侯，高尚其事。"},
  // 18 临
  {"初九：咸临，贞吉。","九二：咸临，吉无不利。","六三：甘临，无攸利。既忧之，无咎。","六四：至临，无咎。","六五：知临，大君之宜，吉。","上六：敦临，吉无咎。"},
  // 19 观
  {"初六：童观，小人无咎，君子吝。","六二：窥观，利女贞。","六三：观我生，进退。","六四：观国之光，利用宾于王。","九五：观我生，君子无咎。","上九：观其生，君子无咎。"},
  // 20 噬嗑
  {"初九：屦校灭趾，无咎。","六二：噬肤灭鼻，无咎。","六三：噬腊肉，遇毒；小吝，无咎。","九四：噬干胏，得金矢，利艰贞，吉。","六五：噬干肉，得黄金，贞厉，无咎。","上九：何校灭耳，凶。"},
  // 21 贲
  {"初九：贲其趾，舍车而徒。","六二：贲其须。","九三：贲如濡如，永贞吉。","六四：贲如皤如，白马翰如，匪寇婚媾。","六五：贲于丘园，束帛戋戋，吝，终吉。","上九：白贲，无咎。"},
  // 22 剥
  {"初六：剥床以足，蔑贞凶。","六二：剥床以辨，蔑贞凶。","六三：剥之，无咎。","六四：剥床以肤，凶。","六五：贯鱼，以宫人宠，无不利。","上九：硕果不食，君子得舆，小人剥庐。"},
  // 23 复
  {"初九：不远复，无祗悔，元吉。","六二：休复，吉。","六三：频复，厉无咎。","六四：中行独复。","六五：敦复，无悔。","上六：迷复，凶，有灾眚。用行师，终有大败，以其国君，凶；至于十年，不克征。"},
  // 24 无妄
  {"初九：无妄，往吉。","六二：不耕获，不菑畲，则利有攸往。","六三：无妄之灾，或系之牛，行人之得，邑人之灾。","九四：可贞，无咎。","九五：无妄之疾，勿药有喜。","上九：无妄，行有眚，无攸利。"},
  // 25 大畜
  {"初九：有厉利已。","九二：舆说輹。","九三：良马逐，利艰贞。曰闲舆卫，利有攸往。","六四：童牛之牿，元吉。","六五：豮豕之牙，吉。","上九：何天之衢，亨。"},
  // 26 颐
  {"初九：舍尔灵龟，观我朵颐，凶。","六二：颠颐，拂经，于丘颐，征凶。","六三：拂颐，贞凶，十年勿用，无攸利。","六四：颠颐吉，虎视眈眈，其欲逐逐，无咎。","六五：拂经，居贞吉，不可涉大川。","上九：由颐，厉吉，利涉大川。"},
  // 27 大过
  {"初六：藉用白茅，无咎。","九二：枯杨生稊，老夫得其女妻，无不利。","九三：栋桡，凶。","九四：栋隆，吉；有它吝。","九五：枯杨生华，老妇得其士夫，无咎无誉。","上六：过涉灭顶，凶，无咎。"},
  // 28 坎
  {"初六：习坎，入于坎窞，凶。","九二：坎有险，求小得。","六三：来之坎坎，险且枕，入于坎窞，勿用。","六四：樽酒簋贰，用缶，纳约自牖，终无咎。","九五：坎不盈，祗既平，无咎。","上六：系用徽纆，寘于丛棘，三岁不得，凶。"},
  // 29 离
  {"初九：履错然，敬之无咎。","六二：黄离，元吉。","九三：日昃之离，不鼓缶而歌，则大耋之嗟，凶。","九四：突如其来如，焚如，死如，弃如。","六五：出涕沱若，戚嗟若，吉。","上九：王用出征，有嘉折首，获匪其丑，无咎。"},
  // 30 咸
  {"初六：咸其拇。","六二：咸其腓，凶，居吉。","九三：咸其股，执其随，往吝。","九四：贞吉悔亡，憧憧往来，朋从尔思。","九五：咸其脢，无悔。","上六：咸其辅颊舌。"},
  // 31 恒
  {"初六：浚恒，贞凶，无攸利。","九二：悔亡。","九三：不恒其德，或承之羞，贞吝。","九四：田无禽。","六五：恒其德，贞，妇人吉，夫子凶。","上六：振恒，凶。"},
  // 32 遁
  {"初六：遁尾，厉，勿用有攸往。","六二：执之用黄牛之革，莫之胜说。","九三：系遁，有疾厉，畜臣妾吉。","九四：好遁，君子吉，小人否。","九五：嘉遁，贞吉。","上九：肥遁，无不利。"},
  // 33 大壮
  {"初九：壮于趾，征凶，有孚。","九二：贞吉。","九三：小人用壮，君子用罔，贞厉。羝羊触藩，羸其角。","九四：贞吉悔亡，藩决不羸，壮于大舆之輹。","六五：丧羊于易，无悔。","上六：羝羊触藩，不能退，不能遂，无攸利，艰则吉。"},
  // 34 晋
  {"初六：晋如，摧如，贞吉。罔孚，裕无咎。","六二：晋如，愁如，贞吉。受兹介福，于其王母。","六三：众允，悔亡。","九四：晋如鼫鼠，贞厉。","六五：悔亡，失得勿恤，往吉无不利。","上九：晋其角，维用伐邑，厉吉无咎，贞吝。"},
  // 35 明夷
  {"初九：明夷于飞，垂其翼。君子于行，三日不食，有攸往，主人有言。","六二：明夷，夷于左股，用拯马壮，吉。","九三：明夷于南狩，得其大首，不可疾贞。","六四：入于左腹，获明夷之心，于出门庭。","六五：箕子之明夷，利贞。","上六：不明晦，初登于天，后入于地。"},
  // 36 家人
  {"初九：闲有家，悔亡。","六二：无攸遂，在中馈，贞吉。","九三：家人嗃嗃，悔厉吉；妇子嘻嘻，终吝。","六四：富家，大吉。","九五：王假有家，勿恤吉。","上九：有孚威如，终吉。"},
  // 37 睽
  {"初九：悔亡，丧马勿逐，自复；见恶人无咎。","九二：遇主于巷，无咎。","六三：见舆曳，其牛掣，其人天且劓，无初有终。","九四：睽孤，遇元夫，交孚，厉无咎。","六五：悔亡，厥宗噬肤，往何咎。","上九：睽孤，见豕负涂，载鬼一车，先张之弧，后说之弧，匪寇婚媾，往遇雨则吉。"},
  // 38 蹇
  {"初六：往蹇，来誉。","六二：王臣蹇蹇，匪躬之故。","九三：往蹇来反。","六四：往蹇来连。","九五：大蹇朋来。","上六：往蹇来硕，吉；利见大人。"},
  // 39 解
  {"初六：无咎。","九二：田获三狐，得黄矢，贞吉。","六三：负且乘，致寇至，贞吝。","九四：解而拇，朋至斯孚。","六五：君子维有解，吉；有孚于小人。","上六：公用射隼于高墉之上，获之，无不利。"},
  // 40 损
  {"初九：已事遄往，无咎，酌损之。","九二：利贞，征凶，弗损益之。","六三：三人行，则损一人；一人行，则得其友。","六四：损其疾，使遄有喜，无咎。","六五：或益之十朋之龟，弗克违，元吉。","上九：弗损益之，无咎，贞吉，利有攸往，得臣无家。"},
  // 41 益
  {"初九：利用为大作，元吉，无咎。","六二：或益之十朋之龟，弗克违，永贞吉。王用享于帝，吉。","六三：益之用凶事，无咎。有孚中行，告公用圭。","六四：中行，告公从。利用为依迁国。","九五：有孚惠心，勿问元吉。有孚惠我德。","上九：莫益之，或击之，立心勿恒，凶。"},
  // 42 夬
  {"初九：壮于前趾，往不胜为咎。","九二：惕号，莫夜有戎，勿恤。","九三：壮于頄，有凶。君子夬夬，独行遇雨，若濡有愠，无咎。","九四：臀无肤，其行次且。牵羊悔亡，闻言不信。","九五：苋陆夬夬，中行无咎。","上六：无号，终有凶。"},
  // 43 姤
  {"初六：系于金柅，贞吉。有攸往，见凶，羸豕孚蹢躅。","九二：包有鱼，无咎，不利宾。","九三：臀无肤，其行次且，厉，无大咎。","九四：包无鱼，起凶。","九五：以杞包瓜，含章，有陨自天。","上九：姤其角，吝，无咎。"},
  // 44 萃
  {"初六：有孚不终，乃乱乃萃，若号，一握为笑，勿恤，往无咎。","六二：引吉，无咎，孚乃利用禴。","六三：萃如，嗟如，无攸利，往无咎，小吝。","九四：大吉，无咎。","九五：萃有位，无咎。匪孚，元永贞，悔亡。","上六：赍咨涕洟，无咎。"},
  // 45 升
  {"初六：允升，大吉。","九二：孚乃利用禴，无咎。","九三：升虚邑。","六四：王用亨于岐山，吉无咎。","六五：贞吉，升阶。","上六：冥升，利于不息之贞。"},
  // 46 困
  {"初六：臀困于株木，入于幽谷，三岁不觌。","九二：困于酒食，朱绂方来，利用亨祀，征凶，无咎。","六三：困于石，据于蒺藜，入于其宫，不见其妻，凶。","九四：来徐徐，困于金车，吝，有终。","九五：劓刖，困于赤绂，乃徐有说，利用祭祀。","上六：困于葛藟，于臲卼，曰动悔。有悔，征吉。"},
  // 47 井
  {"初六：井泥不食，旧井无禽。","九二：井谷射鲋，瓮敝漏。","九三：井渫不食，为我心恻，可用汲，王明，并受其福。","六四：井甃，无咎。","九五：井洌，寒泉食。","上六：井收勿幕，有孚元吉。"},
  // 48 革
  {"初九：巩用黄牛之革。","六二：己日乃革之，征吉，无咎。","九三：征凶，贞厉，革言三就，有孚。","九四：悔亡，有孚改命，吉。","九五：大人虎变，未占有孚。","上六：君子豹变，小人革面，征凶，居贞吉。"},
  // 49 鼎
  {"初六：鼎颠趾，利出否，得妾以其子，无咎。","九二：鼎有实，我仇有疾，不我能即，吉。","九三：鼎耳革，其行塞，雉膏不食，方雨亏悔，终吉。","九四：鼎折足，覆公餗，其形渥，凶。","六五：鼎黄耳金铉，利贞。","上九：鼎玉铉，大吉，无不利。"},
  // 50 震
  {"初九：震来虩虩，后笑言哑哑，吉。","六二：震来厉，亿丧贝，跻于九陵，勿逐，七日得。","六三：震苏苏，震行无眚。","九四：震遂泥。","六五：震往来厉，亿无丧，有事。","上六：震索索，视矍矍，征凶。震不于其躬，于其邻，无咎。婚媾有言。"},
  // 51 艮
  {"初六：艮其趾，无咎，利永贞。","六二：艮其腓，不拯其随，其心不快。","九三：艮其限，列其夤，厉薰心。","六四：艮其身，无咎。","六五：艮其辅，言有序，悔亡。","上九：敦艮，吉。"},
  // 52 渐
  {"初六：鸿渐于干，小子厉，有言，无咎。","六二：鸿渐于磐，饮食衎衎，吉。","九三：鸿渐于陆，夫征不复，妇孕不育，凶；利御寇。","六四：鸿渐于木，或得其桷，无咎。","九五：鸿渐于陵，妇三岁不孕，终莫之胜，吉。","上九：鸿渐于陆，其羽可用为仪，吉。"},
  // 53 归妹
  {"初九：归妹以娣，跛能履，征吉。","九二：眇能视，利幽人之贞。","六三：归妹以须，反归以娣。","九四：归妹愆期，迟归有时。","六五：帝乙归妹，其君之袂，不如其娣之袂良，月几望，吉。","上六：女承筐无实，士刲羊无血，无攸利。"},
  // 54 丰
  {"初九：遇其配主，虽旬无咎，往有尚。","六二：丰其蔀，日中见斗，往得疑疾，有孚发若，吉。","九三：丰其沛，日中见沫，折其右肱，无咎。","九四：丰其蔀，日中见斗，遇其夷主，吉。","六五：来章，有庆誉，吉。","上六：丰其屋，蔀其家，窥其户，阒其无人，三岁不觌，凶。"},
  // 55 旅
  {"初六：旅琐琐，斯其所取灾。","六二：旅即次，怀其资，得童仆贞。","九三：旅焚其次，丧其童仆，贞厉。","九四：旅于处，得其资斧，我心不快。","六五：射雉一矢亡，终以誉命。","上九：鸟焚其巢，旅人先笑后号啕。丧牛于易，凶。"},
  // 56 巽
  {"初六：进退，利武人之贞。","九二：巽在床下，用史巫纷若，吉无咎。","九三：频巽，吝。","六四：悔亡，田获三品。","九五：贞吉悔亡，无不利。无初有终，先庚三日，后庚三日，吉。","上九：巽在床下，丧其资斧，贞凶。"},
  // 57 兑
  {"初九：和兑，吉。","九二：孚兑，吉，悔亡。","六三：来兑，凶。","九四：商兑未宁，介疾有喜。","九五：孚于剥，有厉。","上六：引兑。"},
  // 58 涣
  {"初六：用拯马壮，吉。","九二：涣奔其机，悔亡。","六三：涣其躬，无悔。","六四：涣其群，元吉。涣有丘，匪夷所思。","九五：涣汗其大号，涣王居，无咎。","上九：涣其血，去逖出，无咎。"},
  // 59 节
  {"初九：不出户庭，无咎。","九二：不出门庭，凶。","六三：不节若，则嗟若，无咎。","六四：安节，亨。","九五：甘节，吉；往有尚。","上六：苦节，贞凶，悔亡。"},
  // 60 中孚
  {"初九：虞吉，有它不燕。","九二：鸣鹤在阴，其子和之，我有好爵，吾与尔靡之。","六三：得敌，或鼓或罢，或泣或歌。","六四：月几望，马匹亡，无咎。","九五：有孚挛如，无咎。","上九：翰音登于天，贞凶。"},
  // 61 小过
  {"初六：飞鸟以凶。","六二：过其祖，遇其妣；不及其君，遇其臣；无咎。","九三：弗过防之，从或戕之，凶。","九四：无咎，弗过遇之。往厉必戒，勿用永贞。","六五：密云不雨，自我西郊，公弋取彼在穴。","上六：弗遇过之，飞鸟离之，凶，是谓灾眚。"},
  // 62 既济
  {"初九：曳其轮，濡其尾，无咎。","六二：妇丧其茀，勿逐，七日得。","九三：高宗伐鬼方，三年克之，小人勿用。","六四：繻有衣袽，终日戒。","九五：东邻杀牛，不如西邻之禴祭，实受其福。","上六：濡其首，厉。"},
  // 63 未济
  {"初六：濡其尾，吝。","九二：曳其轮，贞吉。","六三：未济，征凶，利涉大川。","九四：贞吉，悔亡，震用伐鬼方，三年有赏于大国。","六五：贞吉，无悔，君子之光，有孚，吉。","上九：有孚于饮酒，无咎，濡其首，有孚失是。"}
};

const char* yongJiu = "用九：见群龙无首，吉。";
const char* yongLiu = "用六：利永贞。";

// ===== 状态 =====
enum DisplayState { STATE_IDLE, STATE_HEXAGRAM, STATE_RESULT };
DisplayState state = STATE_IDLE;

int benYao[6], bianYao[6];
int changingPos[6], changingCount = 0;
int benIndex = 0, bianIndex = 0;

// ===== 摇卦 =====
int tossYao() {
  int sum = 0;
  for (int i = 0; i < 3; i++) sum += (random(2) == 1) ? 3 : 2;
  return sum;
}

int trigramNum(int bits) {
  switch (bits) {
    case 0b111: return 1; case 0b011: return 2; case 0b101: return 3;
    case 0b001: return 4; case 0b110: return 5; case 0b010: return 6;
    case 0b100: return 7; default: return 8;
  }
}

const int hexLower[64] = {
  1,8,4,6,1,6,6,8,1,2,1,8,3,1,7,8,4,5,2,8,4,3,8,4,4,1,4,5,6,3,7,5,
  7,1,8,3,3,2,7,6,2,4,1,5,8,5,6,5,3,5,4,7,7,2,3,7,5,2,6,2,2,7,3,6
};
const int hexUpper[64] = {
  1,8,6,7,6,1,8,6,5,1,8,1,1,3,8,4,2,7,8,5,3,7,7,8,1,7,7,2,6,3,2,4,
  1,4,3,8,5,3,6,4,7,5,2,1,2,8,2,6,2,3,4,7,5,4,4,3,5,2,5,6,5,4,6,3
};

int computeHexagramIndex(int yao[]) {
  int binary = 0;
  for (int i = 0; i < 6; i++) {
    int yang = (yao[i] == 7 || yao[i] == 9) ? 1 : 0;
    binary |= (yang << i);
  }
  int lo = trigramNum(binary & 0x07);
  int up = trigramNum((binary >> 3) & 0x07);
  for (int i = 0; i < 64; i++)
    if (hexLower[i] == lo && hexUpper[i] == up) return i;
  return 0;
}

// 爻名生成
const char* getYaoName(int pos, int value) {
  bool yang = (value == 7 || value == 9);
  static const char* yangNames[6] = {"初九","九二","九三","九四","九五","上九"};
  static const char* yinNames[6]  = {"初六","六二","六三","六四","六五","上六"};
  return yang ? yangNames[pos] : yinNames[pos];
}

// 绘制单爻（参数化中心与宽度）
void drawYaoAt(int value, int yPos, int centerX, int lineW) {
  int h = 5, left = centerX - lineW/2, right = centerX + lineW/2;
  if (value == 7 || value == 9) {
    tft.fillRect(left, yPos, lineW, h, ST77XX_WHITE);
  } else {
    tft.fillRect(left, yPos, lineW/2 - 3, h, ST77XX_WHITE);
    tft.fillRect(centerX + 3, yPos, lineW/2 - 3, h, ST77XX_WHITE);
  }
  if (value == 6 || value == 9)
    tft.fillCircle(right + 6, yPos + h/2, 2, ST77XX_RED);
}

// 带换行的打印，返回最后一行 y

// ===== 起始页 =====
void showIdleScreen() {
  tft.fillScreen(ST77XX_BLACK);
  u8g2.setForegroundColor(ST77XX_CYAN);
  u8g2.setFont(u8g2_font_wqy16_t_gb2312);
  u8g2.setCursor(10, 60);
  u8g2.print("起卦玩具");
  u8g2.setForegroundColor(ST77XX_WHITE);
  u8g2.setFont(u8g2_font_wqy12_t_gb2312);
  u8g2.setCursor(10, 90);
  u8g2.print("按 BOOT 开始摇卦");
}

// ===== 起卦 + 显示卦象页 =====
// ===== 摇卦并计算（不绘制）=====
void castHexagram() {
  for (int i = 0; i < 6; i++) {
    benYao[i] = tossYao();
    delay(300);
  }
  changingCount = 0;
  for (int i = 0; i < 6; i++) {
    bianYao[i] = benYao[i];
    if (benYao[i] == 6) { bianYao[i] = 7; changingPos[changingCount++] = i; }
    else if (benYao[i] == 9) { bianYao[i] = 8; changingPos[changingCount++] = i; }
  }
  benIndex = computeHexagramIndex(benYao);
  bianIndex = computeHexagramIndex(bianYao);
}

// ===== 绘制第二页（卦象页）=====
void drawHexagramPage() {
  tft.fillScreen(ST77XX_BLACK);
  u8g2.setFont(u8g2_font_wqy12_t_gb2312);
  u8g2.setForegroundColor(ST77XX_YELLOW);

  if (changingCount == 0) {
    u8g2.setCursor(2, 12);
    u8g2.print(hexagramNames[benIndex]);
    u8g2.setForegroundColor(ST77XX_GREEN);
    u8g2.setCursor(100, 12);
    u8g2.print("本卦");

    for (int i = 5; i >= 0; i--)
      drawYaoAt(benYao[i], 30 + (5 - i) * 14, 64, 80);
  } else {
    u8g2.setCursor(2, 12);
    u8g2.print("本卦");
    u8g2.setCursor(68, 12);
    u8g2.print("变卦");

    for (int i = 5; i >= 0; i--) {
      int y = 22 + (5 - i) * 13;
      drawYaoAt(benYao[i],  y, 30, 44);
      drawYaoAt(bianYao[i], y, 96, 44);
    }
    u8g2.setFont(u8g2_font_wqy12_t_gb2312);
    u8g2.setForegroundColor(ST77XX_GREEN);
    u8g2.setCursor(2, 110);
    u8g2.print(hexagramNames[benIndex]);
    u8g2.setCursor(66, 110);
    u8g2.print(hexagramNames[bianIndex]);
  }
}

// ===== 第三页：按变爻个数显示 =====
// ===== 第三页分页数据结构 =====
#define MAX_RESULT_LINES      24
#define MAX_RESULT_LINE_LEN   48
#define RESULT_LINES_PER_PAGE 8

struct ResultLine {
  char text[MAX_RESULT_LINE_LEN];
  uint16_t color;
};

ResultLine resultLines[MAX_RESULT_LINES];
int resultLineCount = 0;
int resultPage = 0;

void clearResultLines() {
  resultLineCount = 0;
}

void addResultLine(const char* text, uint16_t color) {
  if (resultLineCount >= MAX_RESULT_LINES) return;
  strncpy(resultLines[resultLineCount].text, text, MAX_RESULT_LINE_LEN - 1);
  resultLines[resultLineCount].text[MAX_RESULT_LINE_LEN - 1] = 0;
  resultLines[resultLineCount].color = color;
  resultLineCount++;
}

// 把一段 UTF-8 文本按 12px 全角宽折成多行，追加到 resultLines
void addWrappedText(const char* text, uint16_t color, int maxW) {
  char line[MAX_RESULT_LINE_LEN];
  int li = 0, cx = 0;
  const char* p = text;
  while (*p) {
    int len = 1;
    unsigned char c = (unsigned char)*p;
    if ((c & 0xE0) == 0xC0) len = 2;
    else if ((c & 0xF0) == 0xE0) len = 3;
    else if ((c & 0xF8) == 0xF0) len = 4;
    int w = (len > 1) ? 12 : 6;
    if (cx + w > maxW && li > 0) {
      line[li] = 0;
      addResultLine(line, color);
      li = 0; cx = 0;
    }
    if (li + len < MAX_RESULT_LINE_LEN - 1) {
      memcpy(line + li, p, len);
      li += len;
    }
    cx += w;
    p += len;
  }
  if (li > 0) {
    line[li] = 0;
    addResultLine(line, color);
  }
}

// ===== 按 7 种变爻情况生成第三页全部行 =====
void buildResultPage() {
  clearResultLines();
  resultPage = 0;
  const int maxW = 118;
  char label[48];

  switch (changingCount) {
    case 0:
      addResultLine("本卦卦辞", ST77XX_YELLOW);
      addWrappedText(hexagramTexts[benIndex], ST77XX_WHITE, maxW);
      break;

    case 1: {
      int pos = changingPos[0];
      snprintf(label, sizeof(label), "%s·%s", hexagramNames[benIndex], getYaoName(pos, benYao[pos]));
      addResultLine(label, ST77XX_YELLOW);
      addWrappedText(yaoTexts[benIndex][pos], ST77XX_WHITE, maxW);
      break;
    }

    case 2: {
      int hi = changingPos[0] > changingPos[1] ? changingPos[0] : changingPos[1];
      int lo = changingPos[0] < changingPos[1] ? changingPos[0] : changingPos[1];
      addResultLine("本卦二爻", ST77XX_YELLOW);
      snprintf(label, sizeof(label), "%s(主)", getYaoName(hi, benYao[hi]));
      addResultLine(label, ST77XX_CYAN);
      addWrappedText(yaoTexts[benIndex][hi], ST77XX_WHITE, maxW);
      snprintf(label, sizeof(label), "%s(辅)", getYaoName(lo, benYao[lo]));
      addResultLine(label, ST77XX_MAGENTA);
      addWrappedText(yaoTexts[benIndex][lo], ST77XX_WHITE, maxW);
      break;
    }

    case 3: {
      addResultLine("本卦/变卦卦辞", ST77XX_YELLOW);
      addResultLine("本卦(主)", ST77XX_CYAN);
      addWrappedText(hexagramTexts[benIndex], ST77XX_WHITE, maxW);
      snprintf(label, sizeof(label), "变卦:%s(辅)", hexagramNames[bianIndex]);
      addResultLine(label, ST77XX_MAGENTA);
      addWrappedText(hexagramTexts[bianIndex], ST77XX_WHITE, maxW);
      break;
    }

    case 4: {
      int sp[2], n = 0;
      for (int i = 0; i < 6 && n < 2; i++) {
        bool ch = false;
        for (int j = 0; j < changingCount; j++)
          if (changingPos[j] == i) { ch = true; break; }
        if (!ch) sp[n++] = i;
      }
      int lo = sp[0], hi = sp[1];
      addResultLine("变卦二爻", ST77XX_YELLOW);
      snprintf(label, sizeof(label), "%s(主)", getYaoName(lo, bianYao[lo]));
      addResultLine(label, ST77XX_CYAN);
      addWrappedText(yaoTexts[bianIndex][lo], ST77XX_WHITE, maxW);
      snprintf(label, sizeof(label), "%s(辅)", getYaoName(hi, bianYao[hi]));
      addResultLine(label, ST77XX_MAGENTA);
      addWrappedText(yaoTexts[bianIndex][hi], ST77XX_WHITE, maxW);
      break;
    }

    case 5: {
      int pos = -1;
      for (int i = 0; i < 6; i++) {
        bool ch = false;
        for (int j = 0; j < changingCount; j++)
          if (changingPos[j] == i) { ch = true; break; }
        if (!ch) { pos = i; break; }
      }
      snprintf(label, sizeof(label), "%s·%s", hexagramNames[bianIndex], getYaoName(pos, bianYao[pos]));
      addResultLine(label, ST77XX_YELLOW);
      addWrappedText(yaoTexts[bianIndex][pos], ST77XX_WHITE, maxW);
      break;
    }

    case 6:
      if (benIndex == 0) {
        addResultLine("乾·用九", ST77XX_YELLOW);
        addWrappedText(yongJiu, ST77XX_WHITE, maxW);
      } else if (benIndex == 1) {
        addResultLine("坤·用六", ST77XX_YELLOW);
        addWrappedText(yongLiu, ST77XX_WHITE, maxW);
      } else {
        addResultLine("变卦卦辞", ST77XX_YELLOW);
        addWrappedText(hexagramTexts[bianIndex], ST77XX_WHITE, maxW);
      }
      break;
  }
}

// ===== 绘制第三页当前页 =====
void drawResultPage() {
  tft.fillScreen(ST77XX_BLACK);
  u8g2.setFont(u8g2_font_wqy12_t_gb2312);

  int totalPages = (resultLineCount + RESULT_LINES_PER_PAGE - 1) / RESULT_LINES_PER_PAGE;
  if (totalPages == 0) totalPages = 1;
  bool overflow = (totalPages > 1);

  // 溢出时右上角显示页码
  if (overflow) {
    char buf[10];
    snprintf(buf, sizeof(buf), "%d/%d", resultPage + 1, totalPages);
    u8g2.setForegroundColor(COLOR_DIM);
    u8g2.setCursor(102, 12);
    u8g2.print(buf);
  }

  int start = resultPage * RESULT_LINES_PER_PAGE;
  int end = start + RESULT_LINES_PER_PAGE;
  if (end > resultLineCount) end = resultLineCount;

  int y = 14;
  for (int i = start; i < end; i++) {
    u8g2.setForegroundColor(resultLines[i].color);
    u8g2.setCursor(3, y);
    u8g2.print(resultLines[i].text);
    y += 14;
  }

  // 溢出时底部提示操作方式
  if (overflow) {
    u8g2.setFont(u8g2_font_6x12_tr);
    u8g2.setForegroundColor(COLOR_DIM);
    u8g2.setCursor(3, 126);
    u8g2.print("tap:next  hold:home");
  }
}

void setup() {
  Serial.begin(115200);
  delay(200);
  tft.initR(INITR_GREENTAB);
  tft.setRotation(1);
  tft.fillScreen(ST77XX_BLACK);
  u8g2.begin(tft);
  u8g2.setBackgroundColor(ST77XX_BLACK);
  randomSeed(esp_random());
  showIdleScreen();
}

void loop() {
  if (digitalRead(0) == LOW) {
    unsigned long pressStart = millis();
    delay(30); // 消抖
    if (digitalRead(0) == LOW) {
      while (digitalRead(0) == LOW) delay(10); // 等松开
      unsigned long pressDuration = millis() - pressStart;
      bool isLongPress = (pressDuration >= 800);

      // 长按：任何非起始页都回起始页
      if (isLongPress) {
        if (state != STATE_IDLE) {
          showIdleScreen();
          state = STATE_IDLE;
        }
        return;
      }

      // 短按
      switch (state) {
        case STATE_IDLE:
          castHexagram();
          drawHexagramPage();
          state = STATE_HEXAGRAM;
          break;

        case STATE_HEXAGRAM:
          buildResultPage();   // 内部会把 resultPage 重置为 0
          drawResultPage();
          state = STATE_RESULT;
          break;

        case STATE_RESULT: {
          int totalPages = (resultLineCount + RESULT_LINES_PER_PAGE - 1) / RESULT_LINES_PER_PAGE;
          if (totalPages < 1) totalPages = 1;
          resultPage++;
          if (resultPage >= totalPages) {
            // 第三页翻完，回第二页（不重新摇卦）
            drawHexagramPage();
            state = STATE_HEXAGRAM;
          } else {
            drawResultPage();
          }
          break;
        }
      }
    }
  }
}
