((c++-mode . ((eval . (setq flycheck-clang-include-path
                            (list "/home/inmove/.opt/opencv/include/opencv4"
                                  "/usr/local/include")))
              (eval . (setq flycheck-gcc-include-path
                            (list "/home/inmove/.opt/opencv/include/opencv4"
                                  "/usr/local/include"))))))

;; ((c++-mode . ((eval . (setq flycheck-clang-include-path
;;                             (list "/home/inmove/.opt/opencv/include/opencv4"
;;                                   "/usr/local/include"
;;                                   (expand-file-name "include" (locate-dominating-file default-directory "CMakeLists.txt")))))
;;               (eval . (setq flycheck-gcc-include-path
;;                             (list "/home/inmove/.opt/opencv/include/opencv4"
;;                                   "/usr/local/include"
;;                                   (expand-file-name "include" (locate-dominating-file default-directory "CMakeLists.txt")))))))
