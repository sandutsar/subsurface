// SPDX-License-Identifier: GPL-2.0
#ifndef TAGWIDGET_H
#define TAGWIDGET_H

#include "groupedlineedit.h"
#include <QPair>

class QCompleter;

class TagWidget : public GroupedLineEdit {
	Q_OBJECT
public:
	explicit TagWidget(QWidget *parent = 0);
	void setCompleter(QCompleter *completer);
	QPair<int, int> getCursorTagPosition();
	void highlight();
	void setText(const QString &text);
	void clear();
	void setCursorPosition(int position);
	void wheelEvent(QWheelEvent *event);
private
slots:
	void completionSelected(const QString &text);
	void completionHighlighted(const QString &text);

private:
	void keyPressEvent(QKeyEvent *e) override;
	void dragEnterEvent(QDragEnterEvent *e) override;
	void dragLeaveEvent(QDragLeaveEvent *e) override;
	void dragMoveEvent(QDragMoveEvent *e) override;
	void dropEvent(QDropEvent *e) override;
	void focusOutEvent(QFocusEvent *ev) override;
	void inputMethodEvent(QInputMethodEvent *e) override;
	void reparse();
	QCompleter *m_completer;
	bool lastFinishedTag;
};

#endif // TAGWIDGET_H
