hisout = load('hisout.txt');

for i=1:repeat_no
    delfdr = ['TrainingResult_' num2str(i)];
    delete([delfdr '\data.log']);
    delete([delfdr '\SenAna.txt']);
    delete([delfdr '\step.log']);
    delete([delfdr '\test_output.txt']);
    delete([delfdr '\test_target.txt']);
    delete([delfdr '\train_output.txt']);
    delete([delfdr '\train_target.txt']);
    if generalization == 0
        delete([delfdr '\val_output.txt']);
        delete([delfdr '\val_target.txt']);
    end
    
    if hisout(1) == 1
        delete([delfdr '\mu.txt']);
    end
    
    delete([delfdr '\MSE_scaled.txt']);
    
    if generalization == 1
        delete([delfdr '\alphabeta.txt']);
    end
    
    for j=1:M
        exp_tmp = ['delete([delfdr ''\b', num2str(j),'.txt'']);'];
        eval(exp_tmp);
        exp_tmp =['delete([delfdr ''\W', num2str(j),'.txt'']);'];
        eval(exp_tmp);
    end
end

for i=1:repeat_no
    exp_tmp = ['rmdir TrainingResult_', num2str(i),''];
    eval(exp_tmp);
end