#include <QtWidgets>

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    // Create the main window
    QWidget *window = new QWidget;
    window->setWindowTitle("To-Do List");

    // Create a QVBoxLayout to hold the main layout
    QVBoxLayout *mainLayout = new QVBoxLayout;

    // Create a QHBoxLayout for the input area
    QHBoxLayout *inputLayout = new QHBoxLayout;

    // Create QLineEdit for user input
    QLineEdit *lineEdit = new QLineEdit;
    QLabel *dueDateLabel = new QLabel("Due Date:");
    QDateEdit *dueDateEdit = new QDateEdit(QDate::currentDate());
    QPushButton *addButton = new QPushButton("Add");

    // Create a slot to handle task removal
    auto removeTask = [mainLayout](QLabel* label) {
        mainLayout->removeWidget(label);
        label->deleteLater(); // Free memory occupied by the label
    };

    // Connect the button to a slot to add tasks
    QObject::connect(addButton, &QPushButton::clicked, [lineEdit, mainLayout, dueDateEdit, removeTask]() {
        QString task = lineEdit->text();
        QDate dueDate = dueDateEdit->date();
        if (!task.isEmpty()) {
            QLabel *label = new QLabel(task + " (Due: " + dueDate.toString("yyyy-MM-dd") + ")");
            // Provide visual cues for overdue tasks
            if (dueDate < QDate::currentDate()) {
                label->setStyleSheet("QLabel { color : red; }");
            }
            mainLayout->addWidget(label);

            // Connect the label's clicked signal to the removeTask slot
            QObject::connect(label, &QLabel::linkActivated, [label, removeTask](const QString&) {
                removeTask(label);
            });

            lineEdit->clear();
        }
    });

    // Add widgets to the input layout
    inputLayout->addWidget(lineEdit);
    inputLayout->addWidget(dueDateLabel);
    inputLayout->addWidget(dueDateEdit);
    inputLayout->addWidget(addButton);

    // Add the input layout to the main layout
    mainLayout->addLayout(inputLayout);

    // Set the main layout to the window
    window->setLayout(mainLayout);

    // Show the window
    window->show();

    // Execute the application
    return app.exec();
}




