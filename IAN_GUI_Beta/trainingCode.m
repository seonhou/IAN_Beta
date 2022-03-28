system('IAN_Beta.exe');
            
MSE_scaled = zeros(repeat_no,1);
for i=1:repeat_no
    exp_tmp = ['MSE_scaled(i) = load(''TrainingResult_', num2str(i),'\MSE_scaled.txt'');'];
    eval(exp_tmp);
end

[min_value,min_index] = min(MSE_scaled);

bestfdr = ['TrainingResult_' num2str(min_index)];

if generalization == 0
    outputfdr = ['TrainingResult_ES_' num2str(M) '_' num2str(Neuron(1))];
else
    outputfdr = ['TrainingResult_RG_' num2str(M) '_' num2str(Neuron(1))];
end

mkdir(outputfdr);

copyfile(bestfdr, outputfdr);
removeFiles;
            
% RELATIVE ERROR
testtar = load([outputfdr '\test_target.txt']);
testout = load([outputfdr '\test_output.txt']);

clear relerr
testerr = abs(testtar - testout);
maxerr = max(abs(testerr));
relerr = 100*mean(testerr ./ max(abs(testtar)));
MSE = sum(testerr .* testerr)/size(testerr, 1);



%%% testtar = 0 인 경우에 대비하여 처리를 해주어야 함.
%%% RELATIVE DIFFERENCE 를 고려해볼 것

save([outputfdr '\relerr.txt'],'relerr','-ascii');
save([outputfdr '\maxerr.txt'],'maxerr','-ascii');
save([outputfdr '\MSE.txt'],'MSE','-ascii');

for i=1:size(testerr,2)
    exp_tmp = ['h', num2str(i),' = figure(', num2str(i),'); plotregression(testtar(:,', num2str(i),')'', testout(:,', num2str(i),')''); grid on; [reg', num2str(i),',m', num2str(i),',b', num2str(i),'] = regression(testtar(:,', num2str(i),')'', testout(:,', num2str(i),')'');'];
    eval(exp_tmp);
    exp_tmp = ['saveas(h', num2str(i),', [outputfdr ''\regression', num2str(i),'''], ''fig'');'];
    eval(exp_tmp);
end

movefile('setting.log',[outputfdr '\setting.log']);
copyfile('splitinfo.log',[outputfdr '\splitinfo.log']);

delete('info.log');
delete('hisout.txt');

% 아래 것들을 지워버리면 동일 test 데이터로 성능비교가 안됨(즉 새로 split을 해야함)
% 따라서 지우지 않도록 할 것
% delete('test_input.txt');
% delete('test_target.txt');
% delete('train_input.txt');
% delete('train_target.txt');
% delete('val_Q.txt');

close all;