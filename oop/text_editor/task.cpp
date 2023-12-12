#include "task.h"
#include "logged_command_wrapper.h"

/* Курсор влево */
class MoveCursorLeftCommand : public ICommand {
    void Apply(std::string& buffer, size_t& cursorPosition, std::string& clipboard, TextEditor& editor) override {
        editor.UnselectText();
        if (cursorPosition > 0) {
            --cursorPosition;
        }
    }
    void AcceptVisitor(CommandVisitor& visitor) override {
        visitor.VisitMoveCursorLeftCommand(*this);
    }
};

/* Курсор вправо */
class MoveCursorRightCommand : public ICommand {
    void Apply(std::string& buffer, size_t& cursorPosition, std::string& clipboard, TextEditor& editor) override {
        editor.UnselectText();
        if (cursorPosition < buffer.size()) {
            ++cursorPosition;
        }
    }
    void AcceptVisitor(CommandVisitor& visitor) override {
        visitor.VisitMoveCursorRightCommand(*this);
    }
};


/* Курсор вверх */
class MoveCursorUpCommand : public ICommand {
    void Apply(std::string& buffer, size_t& cursorPosition, std::string& clipboard, TextEditor& editor) override {
        editor.UnselectText();
        size_t posThisLine = 0, longPrevLine = 0, start = 0;
        if (buffer[cursorPosition] == '\n') {
            posThisLine = 1;
            --cursorPosition;
        }
        while (cursorPosition >= 0 && buffer[cursorPosition] != '\n') {
            ++posThisLine;
            if (cursorPosition == 0) {
                break;
            }
            --cursorPosition;  
        }
        --posThisLine;
        if (buffer[cursorPosition] == '\n') {
            --cursorPosition;
            ++longPrevLine;
        
            while (cursorPosition >= 0 && buffer[cursorPosition] != '\n') {
                ++longPrevLine;
                if (cursorPosition == 0) {
                    break;
                }
                --cursorPosition;
            }
            if (cursorPosition == 0) {
                start = 0;
            }
            else {
                start = cursorPosition + 1;
            }
            --longPrevLine;
            cursorPosition = start + ((longPrevLine < posThisLine) ? longPrevLine : posThisLine); // min from two didgits
        }
        else {
            cursorPosition += posThisLine;
        }
        
    }
    void AcceptVisitor(CommandVisitor& visitor) override {
        visitor.VisitMoveCursorUpCommand(*this);
    }
};

/* Курсор вниз */
class MoveCursorDownCommand : public ICommand {
    void Apply(std::string& buffer, size_t& cursorPosition, std::string& clipboard, TextEditor& editor) override {
        editor.UnselectText();
        // size_t cursorPosition = 0;
        size_t posThisLine = 0, longNextLine = 0, cursorPosition_ = cursorPosition;
        if (buffer[cursorPosition] == '\n') {
            posThisLine = 1;
            --cursorPosition;
        }
        while (cursorPosition >= 0 && buffer[cursorPosition] != '\n') {
            ++posThisLine;
            if (cursorPosition == 0) {
                break;
            }
            --cursorPosition;
        }
        --posThisLine;
        if (cursorPosition != 0) {
            ++cursorPosition;
        }
        cursorPosition += posThisLine;
        bool nextStr = false;
        size_t start = 0;
        while (cursorPosition < buffer.size()) {
            if (buffer[cursorPosition] == '\n' && nextStr) {
                ++longNextLine;
                break;
            }
            if (nextStr) {
                ++longNextLine;
            }
            if (buffer[cursorPosition] == '\n' && !nextStr) {
                start = cursorPosition + 1;
                nextStr = true;
            }
            ++cursorPosition;
        }
        if (cursorPosition == buffer.size() && !nextStr) {
            
            cursorPosition = cursorPosition_;
        }
        else {
            --longNextLine;
            
            cursorPosition = start + ((longNextLine < posThisLine) ? longNextLine : posThisLine); // min from two didgits
        }
        
    }
    void AcceptVisitor(CommandVisitor& visitor) override {
        visitor.VisitMoveCursorDownCommand(*this);
    }
};

/* Выделить текст */
class SelectTextCommand : public ICommand {
public:
    SelectTextCommand(size_t selectionSize) : selectionSize_(selectionSize) {}

    void Apply(std::string& buffer, size_t& cursorPosition, std::string& clipboard, TextEditor& editor) override {
       editor.UnselectText();
       editor.SelectText(cursorPosition, cursorPosition + selectionSize_);
    }

    void AcceptVisitor(CommandVisitor& visitor) override {
        visitor.VisitSelectCommand(*this);
    }
private:
    size_t selectionSize_;
};

/* Ввести текст */
class InsertTextCommand : public ICommand {
public:
    InsertTextCommand(std::string text) : text_(text) {}
    
    void Apply(std::string& buffer, size_t& cursorPosition, std::string& clipboard, TextEditor& editor) override {
        
        if (!editor.HasSelection()) {
            buffer.insert(cursorPosition, text_);
            cursorPosition += text_.size();
            editor.UnselectText();
        }
        else {
            size_t endSelection = editor.GetSelection().second;
            buffer.erase(cursorPosition, endSelection - cursorPosition);
            buffer.insert(cursorPosition, text_);
            cursorPosition += text_.size(); 
        }
    }
    void AcceptVisitor(CommandVisitor& visitor) override {
        visitor.VisitInsertTextCommand(*this);
    }

private:
    std::string text_;
};

/* Удалить текст */
class DeleteTextCommand : public ICommand {
    void Apply(std::string& buffer, size_t& cursorPosition, std::string& clipboard, TextEditor& editor) override {
        if (editor.HasSelection()) {
            std::pair<size_t, size_t> startEnd = editor.GetSelection();
            buffer.erase(startEnd.first, startEnd.second);
            editor.UnselectText();
        }
        else {
            buffer.erase(cursorPosition, 1);
        }
        
    }
    void AcceptVisitor(CommandVisitor& visitor) override {
        visitor.VisitDeleteTextCommand(*this);
    }
};

/* Скопировать текст */
class CopyTextCommand : public ICommand {
    void Apply(std::string& buffer, size_t& cursorPosition, std::string& clipboard, TextEditor& editor) override {
        
        if (editor.HasSelection()) {
            std::pair<size_t, size_t> startEnd = editor.GetSelection();
            clipboard = buffer.substr(startEnd.first, startEnd.second - startEnd.first);
            editor.UnselectText();
        }
    }
    void AcceptVisitor(CommandVisitor& visitor) override {
        visitor.VisitCopyTextCommand(*this);
    }
};

/* Вставить скопированный текст */
class PasteTextCommand : public ICommand {
    void Apply(std::string& buffer, size_t& cursorPosition, std::string& clipboard, TextEditor& editor) override {
        if (!editor.HasSelection()) {
            buffer.insert(cursorPosition, clipboard);
            cursorPosition += clipboard.size();
        }
        else {
            size_t endSelection = editor.GetSelection().second;
            buffer.erase(cursorPosition, endSelection - cursorPosition);
            buffer.insert(cursorPosition, clipboard);
            editor.UnselectText();
        }
    }

    void AcceptVisitor(CommandVisitor& visitor) override {
        visitor.VisitPasteTextCommand(*this);
    }
};

/* Привести выделенный текст в ВЕРХНИЙ регистр */
class UppercaseTextCommand : public ICommand {
    void Apply(std::string& buffer, size_t& cursorPosition, std::string& clipboard, TextEditor& editor) override {
        
        if (editor.HasSelection()) {
            size_t endSelection = editor.GetSelection().second;
            for (size_t i = cursorPosition; i < endSelection; ++i) {
                buffer[i] = toupper(buffer[i]);
            }
            editor.UnselectText();
        }
    }

    void AcceptVisitor(CommandVisitor& visitor) override {
        visitor.VisitUppercaseTextCommand(*this);
    }
};

/* Привести выделенный текст в нижний регистр */
class LowercaseTextCommand : public ICommand {
    void Apply(std::string& buffer, size_t& cursorPosition, std::string& clipboard, TextEditor& editor) override {
        
        if (editor.HasSelection()) {
            size_t endSelection = editor.GetSelection().second;
            for (size_t i = cursorPosition; i < endSelection; ++i) {
                buffer[i] = tolower(buffer[i]);
            }
            editor.UnselectText();
        }
    }
    void AcceptVisitor(CommandVisitor& visitor) override {
        visitor.VisitLowercaseTextCommand(*this);
    }
};

/* Перенести курсор в конец строки */
class MoveToEndCommand : public ICommand {
    void Apply(std::string& buffer, size_t& cursorPosition, std::string& clipboard, TextEditor& editor) override {
        editor.UnselectText();
        while (cursorPosition < buffer.size()) {
            if (buffer[cursorPosition] == '\n') {
                break;
            }
            ++cursorPosition;
        }
    }
    void AcceptVisitor(CommandVisitor& visitor) override {
        visitor.VisitMoveToEndCommand(*this);
    }
};

/* Перенести курсор в начало строки */
class MoveToStartCommand : public ICommand {
    void Apply(std::string& buffer, size_t& cursorPosition, std::string& clipboard, TextEditor& editor) override {
        
        if (cursorPosition >= buffer.size()) {
            cursorPosition = buffer.size() - 1;
        }
        while (cursorPosition > 0) {
            if (buffer[cursorPosition] == '\n') {
                ++cursorPosition;
                break;
            }
            --cursorPosition;
        }
        editor.UnselectText();
    }
    void AcceptVisitor(CommandVisitor& visitor) override {
        visitor.VisitMoveToStartCommand(*this);
    }
    
};

/* Удалить часть строки, начиная от позиции курсора до первого пробела или конца строки */

class DeleteWordCommand : public ICommand {
    void Apply(std::string& buffer, size_t& cursorPosition, std::string& clipboard, TextEditor& editor) override {
        editor.UnselectText();
        size_t cursorPosition_ = cursorPosition;
        while (cursorPosition < buffer.size()) {
            if (buffer[cursorPosition] == '\n' || buffer[cursorPosition] == ' ') {
                break;
            }
            ++cursorPosition;
        }
        buffer.erase(cursorPosition_, cursorPosition - cursorPosition_);
        cursorPosition = cursorPosition_;
        
    }
    void AcceptVisitor(CommandVisitor& visitor) override {
        visitor.VisitDeleteWordCommand(*this);
    }
};

/* Макрос */
class MacroCommand : public ICommand {
public:
    void AddCommand(CommandPtr& command) {
        commands_.push_back(command);
    }

    void Apply(std::string& buffer, size_t& cursorPosition, std::string& clipboard, TextEditor& editor) override {
        editor.UnselectText();
        for (auto& command : commands_) {
            command->Apply(buffer, cursorPosition, clipboard, editor);
        }
    }

    void AcceptVisitor(CommandVisitor& visitor) override {
        for (auto& command : commands_) {
            command->AcceptVisitor(visitor);
        }
    }

private:
    std::list<CommandPtr> commands_;
};


CommandBuilder::CommandBuilder() : type_(Type::MoveCursorLeft), selectionSize_(0), text_(""), logStreamPtr_(nullptr) {}

CommandPtr CommandBuilder::build() {
    CommandPtr command;
    switch (type_) {
        case Type::MoveCursorLeft:
            command = std::make_shared<MoveCursorLeftCommand>();
            break;
        case Type::MoveCursorRight:
            command = std::make_shared<MoveCursorRightCommand>();
            break;
        case Type::MoveCursorUp:
            command = std::make_shared<MoveCursorUpCommand>();
            break;
        case Type::MoveCursorDown:
            command = std::make_shared<MoveCursorDownCommand>();
            break;
        case Type::SelectText:
            command = std::make_shared<SelectTextCommand>(selectionSize_);
            break;
        case Type::InsertText:
            command = std::make_shared<InsertTextCommand>(text_);
            break;
        case Type::DeleteText:
            command = std::make_shared<DeleteTextCommand>();
            break;
        case Type::CopyText:
            command = std::make_shared<CopyTextCommand>();
            break;
        case Type::PasteText:
            command = std::make_shared<PasteTextCommand>();
            break;
        case Type::UppercaseText:
            command = std::make_shared<UppercaseTextCommand>();
            break;
        case Type::LowercaseText:
            command = std::make_shared<LowercaseTextCommand>();
            break;
        case Type::MoveToEnd:
            command = std::make_shared<MoveToEndCommand>();
            break;
        case Type::MoveToStart:
            command = std::make_shared<MoveToStartCommand>();
            break;
        case Type::DeleteWord:
            command = std::make_shared<DeleteWordCommand>();
            break;
        case Type::Macro:
            auto macroCommand = std::make_shared<MacroCommand>();
            for (auto& v : subcommands_) {
                macroCommand->AddCommand(v);
            }
            command = macroCommand;
            break;
        
    }

    if (logStreamPtr_ != nullptr) {
        return std::make_shared<LoggedCommandWrapper>(*logStreamPtr_, command);
    } 
    else {
        return command;
    }
}


CommandBuilder& CommandBuilder::WithType(Type type) {
    type_ = type;
    return *this;
}

CommandBuilder& CommandBuilder::SelectionSize(size_t selectionSize) {
    selectionSize_ = selectionSize;
    return *this;
}

CommandBuilder &CommandBuilder::Text(std::string text) {
    text_ = text;
    return *this;
}

CommandBuilder& CommandBuilder::LogTo(std::ostream& logStream) {
    logStreamPtr_ = &logStream;
    return *this;
}

CommandBuilder &CommandBuilder::AddSubcommand(CommandPtr subcommand) {
    subcommands_.push_back(subcommand);
    return *this;
}

CommandLoggerVisitor::CommandLoggerVisitor(std::ostream& logStream) : logStream_(logStream) {}

void CommandLoggerVisitor::VisitMoveCursorLeftCommand(MoveCursorLeftCommand& command) {
    logStream_ << 'h';
}

void CommandLoggerVisitor::VisitMoveCursorRightCommand(MoveCursorRightCommand& command) {
    logStream_ << 'l';
}

void CommandLoggerVisitor::VisitMoveCursorUpCommand(MoveCursorUpCommand& command) {
    logStream_ << 'k';
}

void CommandLoggerVisitor::VisitMoveCursorDownCommand(MoveCursorDownCommand& command) {
    logStream_ << 'j';
}

void CommandLoggerVisitor::VisitSelectCommand(SelectTextCommand& command) {
    logStream_ << 'v';
}

void CommandLoggerVisitor::VisitInsertTextCommand(InsertTextCommand& command) {
    logStream_ << 'i';
}

void CommandLoggerVisitor::VisitDeleteTextCommand(DeleteTextCommand& command) {
    logStream_ << 'd';
}

void CommandLoggerVisitor::VisitCopyTextCommand(CopyTextCommand& command) {
    logStream_ << 'y';
}

void CommandLoggerVisitor::VisitPasteTextCommand(PasteTextCommand& command) {
    logStream_ << 'p';
}

void CommandLoggerVisitor::VisitUppercaseTextCommand(UppercaseTextCommand& command) {
    logStream_ << 'U';
}

void CommandLoggerVisitor::VisitLowercaseTextCommand(LowercaseTextCommand& command) {
    logStream_ << 'u';
}

void CommandLoggerVisitor::VisitMoveToEndCommand(MoveToEndCommand& command) {
    logStream_ << '$';
}

void CommandLoggerVisitor::VisitMoveToStartCommand(MoveToStartCommand& command) {
    logStream_ << '0';
}

void CommandLoggerVisitor::VisitDeleteWordCommand(DeleteWordCommand& command) {
    logStream_ << 'd' << 'E';
}





