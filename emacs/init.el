(setq inhibit-startup-message t)

(setq make-backup-files nil)
(setq delete-auto-save-files t)

(setq-default tab-width 4
              indent-tabs-mode nil)

(menu-bar-mode -1)

(tool-bar-mode -1)

(require 'dired-x)

(fset 'yes-or-no-p 'y-or-n-p)

(defun add-cpp-mode-func ()
  (c-set-style "strowstrup")
  (setq c-basic-offset 4)
  )

(add-hook 'c-mode-hook 'add-cpp-mode-func)
(add-hook 'c++-mode-hook 'add-cpp-mode-func)
