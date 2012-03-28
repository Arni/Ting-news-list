/**
 * Behaviour to set up the news list.
 */
Drupal.tingButtons = {};

 Drupal.dialogButton = function (selector, options) {
        var self = this;

        self.defaults = {
            'buttons': function() {}
        };
    self.options = $.extend(self.defaults, options);
    self.selector = selector;

    /**
   * Set up routines.
   */
    self.init = function () {
        var element = $("#news-list-panel");
        var entries = element.find('.reserve-now');
        entries.click(self.buttonClick);
    };

    /**
   * AJAX error handler.
   */
    self.ajaxErrorCallback = function (jqXHR, textStatus, errorThrown) {
        var title = jqXHR.status + ' ' + jqXHR.statusText,
        message = Drupal.t('An error occurred. Please try again, or contact support if the problem persists.');

        self.generateDialog(title, message, self.defaultButtons());
    };

    /**
   * AJAX success handler.
   */
    self.ajaxSuccessCallback = function (data, textStatus, jqXHR) {
        var buttons = self.defaultButtons(), message, title;

        // Message is overwritten by the data attribute.
        title = (data) ? data.title :  Drupal.t('An error occurred.');
        message = (data) ? data.message :  Drupal.t('An error occurred.');
        self.options.buttons(buttons, self.clickEvent, data);
        self.generateDialog(title, message, buttons);
    };

    /**
   * Button click handler.
   */
    self.buttonClick = function (event) {
        self.clickEvent = event;
        if (!$(this).hasClass('disabled')) {
            $.ajax({
                url: this.href,
                dataType: 'json',
                type: 'POST',
                cache: false,
                error: self.ajaxErrorCallback,
                success: self.ajaxSuccessCallback
            });
        }
        else {
            self.generateDialog(Drupal.t('Reservation not allowed'),
                Drupal.t('This material cannot currently be reserved.'),
                self.defaultButtons());
        }

        // Prevent the browser from following the link.
        event.preventDefault();
    };

    /**
   * Generate the default buttons.
   */
    self.defaultButtons = function () {
        var buttons = {};
        buttons[Drupal.t('Close')] = function () {
            $(this).dialog('close');
        };
    };

    /**
   * Generate the jQuery UI dialog response.
   */
    self.generateDialog = function (title, message, buttons) {
        $('<div>' + message + '</div>')
        .dialog({
            'title': title,
            'buttons': buttons,
            'close': function (event, ui) {
                $(this).dialog('destroy').remove();
            }
        });
    };

    self.init();

};

Drupal.behaviors.tingNewsList = function (context) {
    $("#news-list-tabs").tabs();
    //$("#news-list-tabs").removeClass("ui-tabs-nav");
    $(".news-list-tab").each(function (key, value) {
        jQuery.get(Drupal.settings.basePath + 'ting/news_list/ahah/' + Drupal.settings.tingNewsList.destination + "/" + $(value).attr("id"), function (data, status) {
            $(value).html(data);
            Drupal.dialogButton(".reserve-now", '');
            $(value).removeClass("ui-tabs-panel");

        });
    });
}




