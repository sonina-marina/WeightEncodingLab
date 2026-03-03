#include "UI.h"

#include <cstdlib>
#include <memory>

MainWindow::MainWindow(int w, int h, const char* name) {
    window = new Fl_Window(w, h, name);
    window->clear_border();
    window->color(FL_WHITE);
    auto title = std::make_unique<Fl_Box>(200, 15, 760, 30, "Равновесный код");
    title->labelsize(14);
    title->align(FL_ALIGN_LEFT_TOP);
    window->add(title.release());

    Fl_Box* separator = new Fl_Box(0, 40, 760, 2);
    separator->box(FL_FLAT_BOX);
    separator->color(FL_BLACK);
    window->add(separator);

    int firstBorder = 60;
    int secondBorder = 550;
    int yCoord = 70;
    int step = 75;
    int longField = 420;
    int shortField = 150;
    int littleField = 70;
    int littleStep = 30 + littleField;
    int fieldHight = 35;

    //------------------------1 line---------------------------------
    infInput = new Fl_Input(firstBorder, yCoord, longField, fieldHight, "Информационная последовательность");
    infInput->align(FL_ALIGN_TOP);
    infInput->when(FL_WHEN_CHANGED);
    infInput->callback(clearOnInput, this);

    btnInput = new Fl_Button(secondBorder, yCoord, shortField, fieldHight, "ВВОД");
    btnInput->callback(onInput, this);
    btnInput->color(FL_WHITE);

    yCoord += step;

    //------------------------2 line---------------------------------
    mOutput = new Fl_Output(firstBorder, yCoord, littleField, fieldHight, "m");
    mOutput->align(FL_ALIGN_TOP);
    from = new Fl_Box(firstBorder + 1*littleField, yCoord, littleField, fieldHight, "из");
    nOutput = new Fl_Output(firstBorder + 2*littleField, yCoord, littleField, fieldHight, "n");
    nOutput->align(FL_ALIGN_TOP);
    lOutput = new Fl_Output(firstBorder + 3*littleField + 35, yCoord, littleField, fieldHight, "l");
    lOutput->align(FL_ALIGN_TOP);
    ROutput = new Fl_Output(firstBorder + 5*littleField, yCoord, littleField, fieldHight, "R");
    ROutput->align(FL_ALIGN_TOP);

    btnCode = new Fl_Button(secondBorder, yCoord, shortField, fieldHight, "КОДИРОВАТЬ");
    btnCode->color(FL_WHITE);
    btnCode->callback(onCode, this);

    yCoord += step;

    //------------------------3 line---------------------------------
    codeOutput = new Fl_Output(firstBorder, yCoord, longField, fieldHight, "Кодовая комбинация");
    codeOutput->align(FL_ALIGN_TOP);

    aChoice = new Fl_Choice(secondBorder, yCoord, shortField, fieldHight, "a");
    aChoice->align(FL_ALIGN_TOP);

    yCoord += step;

    //------------------------4 line---------------------------------
    codeInput = new Fl_Input(firstBorder, yCoord, longField, fieldHight, "Принятая кодовая комбинация");
    codeInput->align(FL_ALIGN_TOP);
    codeInput->when(FL_WHEN_CHANGED);
    codeInput->callback(clearOnCode, this);

    btnDeCode = new Fl_Button(secondBorder, yCoord, shortField, fieldHight, "ДЕКОДИРОВАТЬ");
    btnDeCode->color(FL_WHITE);
    btnDeCode->callback(onDeCode, this);

    yCoord += step;

    //------------------------5 line---------------------------------
    m2Output = new Fl_Output(firstBorder, yCoord, littleField, fieldHight, "m*");
    m2Output->align(FL_ALIGN_TOP);
    R2Output = new Fl_Output(firstBorder + 2*littleField, yCoord, littleField, fieldHight, "R");
    R2Output->align(FL_ALIGN_TOP);
    rOutput = new Fl_Output(firstBorder + 3*littleField + 35, yCoord, littleField, fieldHight, "r");
    rOutput->align(FL_ALIGN_TOP);
    JOutput = new Fl_Output(firstBorder + 5*littleField, yCoord, littleField, fieldHight, "J");
    JOutput->align(FL_ALIGN_TOP);

    eChoice = new Fl_Choice(secondBorder, yCoord, shortField, fieldHight, "α*");
    eChoice->align(FL_ALIGN_TOP);

    yCoord += step;

    //------------------------6 line---------------------------------
    resultOutput = new Fl_Output(firstBorder, yCoord, longField, fieldHight, "Результат");
    resultOutput->align(FL_ALIGN_TOP);

    btnExit = new Fl_Button(secondBorder, yCoord, shortField, fieldHight, "ВЫХОД");
    btnExit->callback(onExit, this);
    btnExit->color(FL_WHITE);

    //---------------------------------------------------------

    window->end();
}

void MainWindow::show() {
    window->show();
}

void MainWindow::onInput(Fl_Widget*, void* userdata) {
    auto* ui = static_cast<MainWindow*>(userdata);

    if (!validateString(ui->infInput->value(), true)) {
        return;
    }

    infString = ui->infInput->value();

    Answer codingRes = obj.coding(ui->infInput->value());

    ui->mOutput->value(codingRes.m);
    ui->nOutput->value(codingRes.n);
    ui->lOutput->value(codingRes.l);
    ui->ROutput->value(codingRes.R.c_str());
}

void MainWindow::onCode(Fl_Widget*, void* userdata) {
    auto* ui = static_cast<MainWindow*>(userdata);

    if (infString.empty()) {
        return;
    }

    Answer codingRes = obj.coding(infString);
    
    ui->codeOutput->value(codingRes.combination.c_str());
    ui->codeInput->value(ui->codeOutput->value());

    ui->aChoice->clear();
    for (int i = 1; i <= codingRes.m; i++) {
        std::string value = "a" + std::to_string(i) + " = " + std::to_string(codingRes.A[i - 1]);
        ui->aChoice->add(value.c_str());
    }
    ui->aChoice->redraw();
}

void MainWindow::onDeCode(Fl_Widget*, void* userdata) {
    auto* ui = static_cast<MainWindow*>(userdata);

    if (!validateString(ui->codeInput->value(), false)) {
        return;
    }

    std::string check = ui->codeOutput->value();
    if (check.size() == 0) {
        return;
    }

    Answer2 decodingRes = obj.checking(ui->codeInput->value());
    
    ui->m2Output->value(decodingRes.newM);
    ui->R2Output->value(decodingRes.R.c_str());
    ui->rOutput->value(decodingRes.r);
    ui->JOutput->value(decodingRes.J.c_str());
    ui->resultOutput->value(decodingRes.result.c_str());

    ui->eChoice->clear();
    for (int i = 1; i <= decodingRes.newM; i++) {
        std::string value = "a" + std::to_string(i) + " = " + std::to_string(decodingRes.a[i - 1]);
        ui->eChoice->add(value.c_str());
    }
    ui->eChoice->redraw();
}

void MainWindow::onExit(Fl_Widget*, void* userdata) {
    exit(0);
}

void MainWindow::clearOnInput(Fl_Widget*, void* userdata) {
    auto* ui = static_cast<MainWindow*>(userdata);

    ui->codeInput->value("");
    ui->codeOutput->value("");
    ui->mOutput->value("");
    ui->nOutput->value("");
    ui->lOutput->value("");
    ui->m2Output->value("");
    ui->ROutput->value("");
    ui->R2Output->value("");
    ui->rOutput->value("");
    ui->JOutput->value("");
    ui->resultOutput->value("");
    ui->aChoice->clear();
    ui->aChoice->redraw();
    ui->eChoice->clear();
    ui->eChoice->redraw();

    infString = "";
}

void MainWindow::clearOnCode(Fl_Widget*, void* userdata) {
    auto* ui = static_cast<MainWindow*>(userdata);

    ui->m2Output->value("");
    ui->R2Output->value("");
    ui->rOutput->value("");
    ui->JOutput->value("");
    ui->resultOutput->value("");
    ui->eChoice->clear();
    ui->eChoice->redraw();
}

bool MainWindow::validateString(const std::string& s, bool isInf){
    if (s.size() > 10 && isInf) {
        return false;
    }

    for (char c : s) {
        if (c != '0' && c != '1') {
            return false;
        }
    }

    return !s.empty();
}